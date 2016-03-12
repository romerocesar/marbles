/*
 * $Id: input.h 82 2006-11-29 03:54:51Z julio $
 */

#ifndef __INPUT_H
#define __INPUT_H


// callback del teclado cuando se esta editando
void keyboardEdit(unsigned char key, int x, int y);
void specialEdit(int key, int x, int y);
void mouseEdit(int button, int state, int x, int y);
void mouseMotionEdit(int x, int y);

// callback del teclado cuando se esta jugando
void keyboardPlay(unsigned char key, int x, int y);
void specialPlay(int key, int x, int y);


#endif
