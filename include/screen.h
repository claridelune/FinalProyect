#ifndef SCREEN_H_
#define SCREEN_H_

enum TileType { BLANK = 0, STONE, PLAYER, ENEMY, BOMB, FIRE };

class Screen 
{
  private:
    int width;
    int height;
    std::string name;

    int **self;

  public:
    int time = 0;
    int tick = 0;

  public:
    Screen();
    ~Screen();

    void generateTime();
    void generateMap();

    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    int ** getSelf() { return this->self; }

    void create(int, int);
    void assignEntity(Coord, TileType);
    void assignEntity(Coord, Coord, TileType);
    void draw(std::string);
    void draw();
    void nextLevel();
    void display();
};

#endif
