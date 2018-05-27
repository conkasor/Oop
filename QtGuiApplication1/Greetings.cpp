#include "Greetings.h"

void Welcome::exec() {
	
	fl->addRow(greetings);
	fl->addRow(clientMenu, adminMenu);
	fl->addRow(clientViewOnlyMenu);
	fl->setSpacing(10);
	this->show();
	
}
