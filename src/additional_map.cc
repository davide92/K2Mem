#include "additional_map.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::unordered_map;
using std::make_pair;
using std::vector;

namespace kraken2 {

	bool is_empty(std::ifstream& pFile) {
    	return pFile.peek() == ifstream::traits_type::eof();
	}

	AdditionalHashMap::AdditionalHashMap(const std::string &filename, const std::string &add_opts_filename) {
		AdditionalHashMap(filename.c_str(), add_opts_filename.c_str());
	}
	
	AdditionalHashMap::AdditionalHashMap(const char *filename, const char *add_opts_filename) {

		//get the size of the hashmap
		ifstream ifs_opts(add_opts_filename);
		if (!is_empty(ifs_opts)){
			ifs_opts.read((char *) &total_size, sizeof(total_size));
		}
		ifs_opts.close();


		ifstream ifs(filename);
		if (!is_empty(ifs)){
			uint64_t key[total_size];			
			taxid_t value[total_size];

			ifs.read((char *) &key, total_size * sizeof(uint64_t));
	    	if (! ifs) {
	      		errx(EX_OSERR, "Error reading key in additional hash table");
	    	}

	    	ifs.read((char *) &value, total_size * sizeof(taxid_t));
	    	if (! ifs) {
	      		errx(EX_OSERR, "Error reading value in additional hash table");
	    	}

	    	ifs.close();

	    	for (size_t i = 0; i != total_size; ++i) {
	    		ump.insert(make_pair(key[i], value[i]));
	    	}

			total_size = ump.size();
		} else {
			ifs.close();
		}

	}

	void AdditionalHashMap::AddPair(uint64_t minimizer, taxid_t tax_id, Taxonomy &taxonomy) {
		taxid_t new_tax = tax_id;
		taxid_t old_tax = 0;

		if (ump.find(minimizer) != ump.end())	{
			old_tax = ump[minimizer];
			new_tax = taxonomy.LowestCommonAncestor(new_tax, old_tax);
		}

		ump.insert(make_pair(minimizer, new_tax));
		total_size = ump.size();
	}
	
	taxid_t AdditionalHashMap::GetTax(uint64_t minimizer) {
		taxid_t tax = 0;

		if (ump.find(minimizer) != ump.end()) {
			tax = ump[minimizer];
		}
		
		return tax;
	}
	
	size_t AdditionalHashMap::GetSize() {
		return ump.size();
	}

	bool AdditionalHashMap::IsEmpty(){
		return ump.size() == 0;
	}
	
	void AdditionalHashMap::WriteHashMap(const char *filename, const char *add_opts_filename) {
		//save the size of the hashmap
		ofstream ofs_opts(add_opts_filename, ofstream::binary);
  		ofs_opts.write((char *) &total_size, sizeof(total_size));
  		ofs_opts.close();


  		//save hashmap
  		vector<uint64_t> key;
  		vector<taxid_t> value;

   		for (auto element : ump) {
  			key.push_back(element.first);
  			value.push_back(element.second);
  		}

  		ofstream ofs(filename, ofstream::binary);
  		ofs.write((char *) key.data(), sizeof(uint64_t) * total_size);
  		ofs.write((char *) value.data(), sizeof(taxid_t) * total_size);
  		ofs.close();
	}
}