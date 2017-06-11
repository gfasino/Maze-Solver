#include <iostream>
#include "cvgui.h"
#include <vector>

int main(int argc, char* argv[]){
	std::vector<std::string> all_args;
	all_args.assign(argv + 1, argv + argc);

	if(argc < 2){
		std::cout << "missing arguments" << '\n';
		return -1;
	}

	bool delay = 0;
	int heu = 0;
	int postopt = 0;

	for(int i=0; i<all_args.size(); i++){
		if(all_args[i] == "-d"){
			delay = 5;
		}
		if(all_args[i] == "-h0"){
			heu = 0;
		}
		if(all_args[i] == "-h1"){
			heu = 1;
		}
		if(all_args[i] == "-h2"){
			heu = 2;
		}
		if(all_args[i] == "-h3"){
			heu = 3;
		}

		if(all_args[i] == "--help" || all_args[i] == "-h"){
			std::cout<<"Usage:\n";
			std::cout<<"./mazesolver path/to/file.jpg [params]\n";
			std::cout<<"\nParameters:\n";
			std::cout<<"Search Algorithm: (default 0)\n";
			std::cout<<"\t-h0\t Queue Search \n";
			std::cout<<"\t-h1\t Best Path\n";
			std::cout<<"\t-h2\t Combinatory + Heuristic 1 \n";
			std::cout<<"\t-h3\t Combinatory + Heuristic 2 \n";
			std::cout<<"\nOther:\n";
			std::cout<<"\t-d\tslowdown execution\n";
			std::cout<<"\t-h\tshow this help\n";
			std::cout<<"\t--help\n";
			std::cout<<"\nRuntime keys:\n";
			std::cout<<"\t0-3\tchange search algorithm\n";
			std::cout<<"\ts\tslowdown execution\n";
			std::cout<<"\tf\ttake a screenshot\n";
			return -1;
		}
	}

	CVGui cx(argv[1], heu, delay);
	cx.start();

	return 0;
}
