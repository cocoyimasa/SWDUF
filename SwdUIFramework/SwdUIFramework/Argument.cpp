#include "Argument.h"

Argument::Argument(){

}
Argument::Argument(const Argument& args){
	this->args.assign(args.args.begin(),args.args.end());
}
Object* Argument::Get(int index){
	if (index >= args.size()){
		return NULL;
	}
	else{
		return args[index];
	}
}
void Argument::Push(Object* obj){
	args.push_back(obj);
}
bool Argument::Clear(){
	this->args.clear();
	if (this->args.size() != 0){
		return false;
	}
	return true;
}
int Argument::Size(){
	return args.size();
}