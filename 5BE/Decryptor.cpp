#include "Decryptor.h"


Decryptor::~Decryptor() {
	delete this->key;
	delete this->iv;
}