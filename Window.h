#pragma once
class Window {
public:
    virtual int show() = 0; 
    virtual void close() = 0;
    virtual ~Window() = default;
};