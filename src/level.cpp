#include "../include/basic.h"

Level::Level(Screen & screen_, Player *& player_, int numberEnemies_) :
  screen(screen_), player(player_), interface(player_)
{
  this->isActive = true;
	this->isCompleted = false;
  this->numberEnemies = numberEnemies_;
  this->enemies = new Normal[this->numberEnemies];

  this->player->setPosition({ 1, screen_.getHeight() });
}

Level::~Level()
{
  ;
}

void Level::generateMap(Screen & screen_)
{
  int rows = screen_.getHeight();
  int cols = screen_.getWidth();

  for (int i = 0; i < rows + 2; i++) {
    for (int j = 0; j < cols + 2; j++) {
      if (i == 0 || j == 0 || i == (rows + 2) - 1 || j == (cols + 2) - 1) {
        screen_.getSelf()[i][j] = TileType::STONE;
      } else {
        screen_.getSelf()[i][j] = TileType::BLANK;
      }
    }
  }

  int FParedes = 8;
  int den = (rows+2) * (cols+2) / 4;
  for (int i = 0; i < den; i++) {
    int x = rand() % ((cols+2) - 4) + 2;
    x = (x / 2) * 2; // tiene que ser par
    int y = rand() % ((rows+2) - 4) + 2;
    y = (y / 2) * 2;
    screen_.getSelf()[y][x] = TileType::STONE;
    for (int j = 0; j < FParedes; j++) { // crear matrices para las paredes
      int mx[4] = {x, x, x + 2, x - 2};
      int my[4] = {y + 2, y - 2, y, y};
      int r = rand() % 4; // 0-3, escoger un indice de la matriz

      if (screen_.getSelf()[my[r]][mx[r]] == TileType::BLANK) {
        screen_.getSelf()[my[r]][mx[r]] = TileType::STONE;
        screen_.getSelf()[my[r] + (y - my[r]) / 2][mx[r] + (x - mx[r]) / 2] = TileType::STONE;
      }
    }
  }
}

void Level::generateEnemy(Screen & screen_)
{
  int rows = screen_.getHeight();
  int cols = screen_.getWidth();

  // srand(time(NULL));
  int x, y;
  for (int i = 0; i < this->numberEnemies; i++) {
    do{
      y = rand()% rows + 1;
            /* if (y < (rows / 3)) {
              x = rand() % cols + 1;
            } else {
              x = rand() % cols + (3 * cols / 4);
            } */
            x = rand() % cols + 1;
    } while(screen_.getSelf()[y][x]!=0);
    enemies[i].setPosition({x, y});
    enemies[i].setRandomDirection();
  }
}

void Level::checkCollisions(Screen & screen_)
{
  // int rows = screen_.getHeight();
  // int cols = screen_.getWidth();
    
  Coord position = player->getPosition();
  switch(screen_.getSelf()[position.Y][position.X])
  {
    case TileType::ENEMY:
      this->isCompleted = true;
      break;
    case TileType::STONE:
      player->setPosition(player->getLastPosition());
      break;
    default:
      break;
  }

  for (int i = 0; i < numberEnemies; i++) {
    Coord enemyPosition = enemies[i].getPosition();
    switch (screen_.getSelf()[enemyPosition.Y][enemyPosition.X]) {
      case TileType::STONE:
        enemies[i].setPosition(enemies[i].getLastPosition());
        enemies[i].setRandomDirection();
        break;
      default: break;
      }
  }
}

void Level::update()
{
   for (int i = 0; i < numberEnemies; i++) {
    enemies[i].update();
   }

  this->player->update();
}

void Level::draw(Screen & screen_)
{
  // Pendiente de movear al screen
  int rows = screen_.getHeight();
  int cols = screen_.getWidth();

  for (int i = 0; i < rows + 2; i++) {
    for (int j = 0; j < cols + 2; j++) {
      switch (screen_.getSelf()[i][j]) {
      case TileType::STONE:
        std::cout << ":3";
        break;
      case TileType::PLAYER:
        std::cout << BLUE << "<>" << NC;
        break;
      case TileType::ENEMY:
        std::cout << RED << "/\\" << NC;
        break;
      default:
        std::cout << "  ";
        break;
      }
    }

    std::cout << "\n";
    }

  screen_.assignEntity(player->getLastPosition(), player->getPosition(), TileType::PLAYER);
  for (int i = 0; i < numberEnemies; i++) {
    Coord position = enemies[i].getPosition();

    std::cout << position.X << "-" << position.Y << std::endl;

    if (position.X >= 1 && position.X <= cols && position.Y >= 1 && position.Y <= rows) {
      screen_.assignEntity(enemies[i].getLastPosition(), enemies[i].getPosition(), TileType::ENEMY);
    }
  }
  
  this->screen.display();
}

bool Level::play(Screen & screen_, Player *& player_)
{
  this->generateMap(screen_);
  this->generateEnemy(screen_);

  while(!this->isCompleted)
  {
    this->update();
    this->checkCollisions(screen_);
    this->draw(screen_);
  }

  return this->isCompleted;
}