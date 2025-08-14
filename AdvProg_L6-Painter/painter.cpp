#include "painter.h"

/***
    Args: color (SDL_Color): color value 
        
    Returns:
        None
***/
void Painter::setColor(SDL_Color color) 
{ 
    this->color = color;
}


/***
    Args: numPixel (int): number of pixel for jumping forward
        
    Returns:
        None
***/
void Painter::jumpForward(int numPixel)
{
	double rad = (angle / 180) * M_PI;
	setPosition(x + (int) (cos(rad) * (double) numPixel),
				y - (int) (sin(rad) * (double) numPixel));
}


/***
    Args: numPixel (int): number of pixel for jumping backward
        
    Returns:
        None
***/
void Painter::jumpBackward(int numPixel)
{
	double rad = (angle / 180) * M_PI;
	setPosition(x - (int) (cos(rad) * (double) numPixel),
				y + (int) (sin(rad) * (double) numPixel));
}


/***
    Args: degree (double): the value of rotation angle
        
    Returns:
        None
***/       
void Painter::turnLeft(double degree)
{
    // TODO: rotate left the painter
	setAngle(angle + degree);
}


/***
    Args: degree (double): the value of rotation angle
        
    Returns:
        None
***/     
void Painter::turnRight(double degree)
{
    // TODO: rotate right the painter  
	setAngle(angle - degree);
}

/***  
    Args: 
        None
    Returns:
        None
***/
void Painter::randomColor()
{
	SDL_Color randomColor;
	randomColor.r = rand() % 256;
	randomColor.g = rand() % 256;
	randomColor.b = rand() % 256;
	randomColor.a = 255;
	setColor(randomColor);
}


/***
Part of code that not need to be implemented
***/
void Painter::clearWithBgColor(SDL_Color bgColor)
{
    SDL_Color curColor = color;
    setColor(bgColor);
	SDL_RenderClear(renderer);    
    setColor(curColor);
}


Painter::Painter(SDL_Window* window, SDL_Renderer *renderer)
{
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0) {
        SDL_GetWindowSize(window, &width, &height);
    }
    this->renderer = renderer;
    setPosition(width/2, height/2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}


void Painter::createCircle(int radius)
{
    double rad = (angle / 180) * M_PI;
    int centerX = x + (int) (cos(rad) * (double) radius);;
    int centerY = y - (int) (sin(rad) * (double) radius);;

    int dx = radius;
    int dy = 0;
    int err = 0;

    while (dx >= dy)
    {
        SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
        SDL_RenderDrawPoint(renderer, centerX + dy, centerY + dx);
        SDL_RenderDrawPoint(renderer, centerX - dy, centerY + dx);
        SDL_RenderDrawPoint(renderer, centerX - dx, centerY + dy);
        SDL_RenderDrawPoint(renderer, centerX - dx, centerY - dy);
        SDL_RenderDrawPoint(renderer, centerX - dy, centerY - dx);
        SDL_RenderDrawPoint(renderer, centerX + dy, centerY - dx);
        SDL_RenderDrawPoint(renderer, centerX + dx, centerY - dy);

        if (err <= 0)
        {
            dy += 1;
            err += 2*dy + 1;
        }
        if (err > 0)
        {
            dx -= 1;
            err -= 2*dx + 1;
        }
    }
}



void Painter::createParallelogram(int size)
{
	for (int i = 0; i < 2; ++i) {
        moveForward(size);
        turnLeft(60);
        moveForward(size);
        turnLeft(120);
    }	
}



void Painter::createSquare(int size)
{
	for (int i = 0; i < 4; ++i) {
        moveForward(size);
	    turnLeft(90);
    }
}


void Painter::moveForward(int numPixel)
{
    int preX = x, preY = y;
    jumpForward(numPixel);
    SDL_RenderDrawLine(renderer, preX, preY, x, y);
}


void Painter::moveBackward(int numPixel)
{
    moveForward(-numPixel);
}

