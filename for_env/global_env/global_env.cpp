#include <stdlib.h>
#include <stdio.h>
#include <iostream>

struct KBEEnv
{
	std::string path;
	std::string root_path;
	std::string res_path;
	std::string bin_path;
};

int main(void)
{
	KBEEnv kbe_env;
	kbe_env.path = getenv("PATH") == NULL ? "" : getenv("PATH");
	kbe_env.root_path = getenv("KBE_ROOT") == NULL ? "" : getenv("KBE_ROOT");
	kbe_env.res_path = getenv("KBE_RES_PATH") == NULL ? "" : getenv("KBE_RES_PATH");
	kbe_env.bin_path = getenv("KBE_BIN_PATH") == NULL ? "" : getenv("KBE_BIN_PATH");
	printf("p_kbe_env: %s\n%s\n%s\n%s\n", 
		kbe_env.path.c_str(),
		kbe_env.root_path.c_str(),
		kbe_env.res_path.c_str(), 
		kbe_env.bin_path.c_str());
}