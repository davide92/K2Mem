#include "additional_map.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istringstream;
using std::unordered_map;
using std::vector;

namespace kraken2 {

	bool is_empty(std::ifstream& pFile) {
    	return pFile.peek() == ifstream::traits_type::eof();
	}
	
	void AdditionalMap::ReadFile(const char *filename) {

	    ifstream ifile(filename);

	    if(ifile.is_open() && !is_empty(ifile)) {

	    	while (!ifile.eof()) {
	    		string line;
	    		uint64_t key;
    			taxid_t value;

	    		getline(ifile, line);
	    		istringstream linestream(line);    		
	    		linestream >> key >> value;

    			Add(key, value);    		
	    	}
	    } else if (!ifile.is_open()) {
	    	ofstream outfile (filename);
			outfile << "";
			outfile.close();
	    }

	    ifile.close();
	}

	void AdditionalMap::AddPair(uint64_t minimizer, taxid_t tax_id, Taxonomy &taxonomy) {
		taxid_t new_tax = tax_id;
		taxid_t old_tax = 0;

		if (ump.find(minimizer) != ump.end())	{
			old_tax = ump[minimizer];
			new_tax = taxonomy.LowestCommonAncestor(new_tax, old_tax);
			ump[minimizer] = new_tax;
		} else {
			Add(minimizer, new_tax);
		}
	}

	void AdditionalMap::Add(uint64_t minimizer, taxid_t tax_id) {
		ump.emplace(minimizer, tax_id);
	}
	
	taxid_t AdditionalMap::GetTax(uint64_t minimizer) {
		taxid_t tax = 0;

		if (ump.find(minimizer) != ump.end()) {
			tax = ump[minimizer];
		}
		
		return tax;
	}	
	
	size_t AdditionalMap::GetSize() {
		return ump.size();
	}

	bool AdditionalMap::IsEmpty(){
		return ump.size() == 0;
	}
	
	void AdditionalMap::WriteMap(const char *filename) {
		
		if (GetSize()) {
			ofstream ofile(filename);
	    	if (ofile.is_open()) {
				for (auto x: ump)  {
			        ofile << x.first << "\t" << x.second;
			        ofile << "\n";
			    }
	    	}

			ofile.close();	  		
		}
	}
}