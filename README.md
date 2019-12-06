Kraken 2 plus
=============

Kraken 2 plus is a variant of [Kraken 2](https://genomebiology.biomedcentral.com/articles/10.1186/s13059-019-1891-0) taxonomic sequence classification system.  
Kraken 2 plus, compared to Kraken 2, can learn from the previous classifications.

Installation
------------
Selected an install directory, you need to run the following command in the directory where you have the Kraken 2 plus source:

    ./install_kraken2_plus.sh $KRAKEN2_DIR

(Replace `$KRAKEN2_DIR` above with the directory where you want to install (Kraken 2 plus's programs/scripts.)

Standard database
-----------------
To create the standard database, you can use the following command:

    kraken2-build --standard --db $DBNAME

(Replace "`$DBNAME`" above with your preferred database name/location.)

Classification
--------------
To classify a set of sequences, use the `kraken2` command:

    kraken2 --db $DBNAME seqs.fa

To classify a set of sequences using the informations obtained from the previous classifications, use the `kraken2-plus` command:

    kraken2-plus --db $DBNAME seqs.fa

in both cases output will be sent to standard output by default.

To get a full list of options, use `kraken2 --help` or `kraken2-plus --help`.

References
----------
[Kraken 2 webpage](https://ccb.jhu.edu/software/kraken2/)  
[Kraken 2 manual](https://ccb.jhu.edu/software/kraken2/index.shtml?t=manual)