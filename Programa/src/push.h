#ifndef PUSH_H
#define PUSH_H

#include "button.h"

class Push : public Button{
	public:
		Push(short const pin);
		virtual bool pushed(void) override;
};
#endif// PUSH_H

