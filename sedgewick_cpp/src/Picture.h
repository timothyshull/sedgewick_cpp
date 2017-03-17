#ifndef PICTURE_H
#define PICTURE_H

#include <string>

class Picture {
public:
    Picture(int width, int height);

    Picture(Picture& picture);

    Picture(File& file);

    Label getJLabel();

    void setOriginUpperLeft();

    void show();

    inline int height() const noexcept { return height; }

    inline int width() const noexcept { return width; }

    Color get(int col, int row);

    void set(int col, int row, Color& color);

    bool operator==(const Picture& rhs);

    // std::size_t hash_code(); unsupported

    void save(std::string& filename);

    void save(File& file);

    void action_performed(Action_event& e);

private:
    Buffered_image image;
    Frame frame;
    std::string filename;
    bool isOriginUpperLeft = true;
    const int width;
    const int height;

};

#endif // PICTURE_H
