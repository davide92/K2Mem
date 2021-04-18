/*
 * Copyright 2013-2019, Derrick Wood <dwood@cs.jhu.edu>
 *
 * This file is part of the Kraken 2 taxonomic sequence classification system.
 */

#include "utilities.h"

using std::vector;
using std::string;

namespace kraken2 {

void ExpandSpacedSeedMask
  (uint64_t &spaced_seed_mask, const int bit_expansion_factor)
{
  uint64_t new_mask = 0;
  uint64_t bits = 1 << bit_expansion_factor;
  bits--;

  for (int i = 64 / bit_expansion_factor - 1; i >= 0; i--) {
    new_mask <<= bit_expansion_factor;
    if ((spaced_seed_mask >> i) & 1)
      new_mask |= bits;
  }
  spaced_seed_mask = new_mask;
}

vector<string> SplitString
  (const string &str, const string &delim, const size_t max_fields)
{
  vector<string> output;
  size_t pos1, pos2;
  pos1 = 0;
  size_t field_ct = 0;
  bool finished = false;
  while (field_ct++ < max_fields && ! finished) {  // tokenizing loop
    pos2 = str.find(delim, pos1);
    string token;
    if (pos2 == string::npos) {
      token = str.substr(pos1);
      finished = true;
    }
    else {
      token = str.substr(pos1, pos2 - pos1);
      pos1 = pos2 + delim.size();
    }
    output.push_back(token);
  }
  return output;
}

bool IsSpecies(Taxonomy &tax, TaxonomyNode &node) 
{ 
  bool is_species = false;
  string rank = tax.rank_data() + node.rank_offset;

  if (rank == "species") {
    is_species = true;
  }

  return is_species;
}

bool IsGenus(Taxonomy &tax, TaxonomyNode &node) 
{ 
  bool is_genus = false;
  string rank = tax.rank_data() + node.rank_offset;
  
  if (rank == "genus") {
    is_genus = true;
  }

  return is_genus;
}

bool IsOther(Taxonomy &tax, TaxonomyNode &node) 
{
  bool is_other = false;
  string rank = tax.rank_data() + node.rank_offset;
  
  if (rank == "root" || rank == "superkingdom" || rank == "kingdom" 
    || rank == "phylum" || rank == "class" || rank == "order" || rank == "family") {
    is_other = true;
  }

  return is_other; 
}

}