#ifndef KRAKEN2_ADDITIONAL_HASH_H_
#define KRAKEN2_ADDITIONAL_HASH_H_

#include "kraken2_headers.h"
#include "kraken2_data.h"
#include "taxonomy.h"

namespace kraken2 {

	class AdditionalHashMap {
	  public:
	  AdditionalHashMap(const std::string &filename, const std::string &add_opts_filename);
	  AdditionalHashMap(const char *filename, const char *add_opts_filename);

	  void AddPair(uint64_t minimizer, taxid_t tax_id, Taxonomy &taxonomy);
	  taxid_t GetTax(uint64_t minimizer);
	  size_t GetSize();
	  void WriteHashMap(const char *filename, const char *add_opts_filename);
	  bool IsEmpty();


	  private:
	  std::unordered_map<uint64_t, taxid_t> ump;
	  size_t total_size = 0;
	  
	};

}

#endif