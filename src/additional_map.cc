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
	
	void AdditionalHashMap::ReadFile(const char *filename) {

		/*ifstream ifs(filename, ifstream::binary);

		if (ifs) {
			if (!is_empty(ifs)){
			ifs.read((char *) &total_size, sizeof(total_size));

			vector<uint64_t> key(total_size);
			vector<taxid_t> value(total_size);

			ifs.read((char *) key.data(), total_size * sizeof(key.data()));
	    	if (! ifs) {
	      		errx(EX_OSERR, "Error reading key in additional hash table");
	    	}

	    	ifs.read((char *) value.data(), total_size * sizeof(value.data()));
	    	if (! ifs) {
	      		errx(EX_OSERR, "Error reading key in additional hash table");
	    	}

	    	ifs.close();

	    	for (size_t i = 0; i != total_size; ++i) {
	    		ump.insert(make_pair(key[i], value[i]));
	    	}

	    	key.clear();
	    	value.clear();

			} else {
				ifs.close();
			}
		}*/

		/*fstream ifile(filename);

	    if(ifile.is_open() && !is_empty(ifile)) {
	    	cout << "parse additional map file." << endl;

	    	std::unordered_map<uint64_t, taxid_t> tmp_ump;

	    	while (!ifile.eof()) {
	    		string line;
	    		uint64_t key;
    			taxid_t value;

	    		getline(ifile, line);
	    		istringstream linestream(line);    		
	    		linestream >> key >> value;

    			tmp_ump.emplace(key, value);    		
	    	}

		    ifile.close();
		    ump(tmp_ump);
	    }*/

	    ifstream ifile(filename);

	    if(ifile.is_open() && !is_empty(ifile)) {
	    	cout << "parse additional map file." << endl;

	    	while (!ifile.eof()) {
	    		string line;
	    		uint64_t key;
    			taxid_t value;

	    		getline(ifile, line);
	    		istringstream linestream(line);    		
	    		linestream >> key >> value;

    			Add(key, value);    		
	    	}

		    ifile.close();
	    } 
		
	}

	void AdditionalHashMap::AddPair(uint64_t minimizer, taxid_t tax_id, Taxonomy &taxonomy) {
		taxid_t new_tax = tax_id;
		taxid_t old_tax = 0;

		if (ump.find(minimizer) != ump.end())	{
			old_tax = ump[minimizer];
			new_tax = taxonomy.LowestCommonAncestor(new_tax, old_tax);
		}

		ump.emplace(minimizer, new_tax);
	}

	void AdditionalHashMap::Add(uint64_t minimizer, taxid_t tax_id) {
		ump.emplace(minimizer, tax_id);
	}
	
	taxid_t AdditionalHashMap::GetTax(uint64_t minimizer) {
		taxid_t tax = 0;

		if (ump.find(minimizer) != ump.end()) {
			tax = ump[minimizer];
		}
		
		return tax;
	}	
	
	size_t AdditionalHashMap::GetSize() {
		/*if ( ump.size() != total_size) {
			total_size = ump.size();
		}
		return total_size;*/
		return ump.size();
	}

	bool AdditionalHashMap::IsEmpty(){
		return ump.size() == 0;
	}
	
	void AdditionalHashMap::WriteHashMap(const char *filename) {
		
		/*if (ump.GetSize()) {
			vector<uint64_t> key(total_size);
	  		vector<taxid_t> value(total_size);

	  		size_t i = 0;
	   		for (auto element : ump) {
	  			key[i] = element.first;
	  			value[i] = element.second;
	  			++i;
	  		}

			ofstream ofs(filename, ofstream::binary);
			ofs.write((char *) &total_size, sizeof(total_size));

	  		ofs.write((char *) key.data(), total_size * sizeof(key.data()));
	  		ofs.flush();
	  		ofs.write((char *) value.data(), total_size * sizeof(value.data()));		
	  		
	  		ofs.close();

	  		key.clear();
		    value.clear();
		}
  		
	}*/

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