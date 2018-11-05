#ifndef DRAWER_H
#define DRAWER_H

class Drawer
{
public:
    virtual ~Drawer() {}

    virtual void draw() const = 0;
};

#endif // DRAWER_H
