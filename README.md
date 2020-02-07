K2Mem
=====

The major problem when analyzing a metagenomic sample is to taxonomically annotate its reads in order to identify the species they contain.
Most of the methods currently available focus on the classification of reads using a set of reference genomes and their k-mers. While in terms of precision these methods have reached percentages of correctness close to perfection, in terms of recall (the actual number of classified reads) the performances fall at around 50%. 
One of the reasons is the fact that the sequences in a sample can be very different from the corresponding reference genome, e.g. viral genomes are highly mutated.  
To address this issue, in this paper we study the problem of metagenomic reads classification by improving the reference k-mers library with novel discriminative k-mers from the input sequencing reads. We evaluated the performance in different conditions against several other tools and the results showed an improved F-measure, especially when close reference genomes are not available. 

Installation
------------
Selected an install directory, you need to run the following command in the directory where you have the K2Mem source:

    ./install_k2mem.sh $KRAKEN2_DIR

(Replace `$KRAKEN2_DIR` above with the directory where you want to install (K2Mem's programs/scripts.)

Standard database
-----------------
To create the standard database, you can use the following command:

    k2mem-build --standard --db $DBNAME

(Replace `$DBNAME` above with your preferred database name/location.)

Classification
--------------
To classify a set of sequences using the informations obtained from the previous classifications, use the `k2mem` command:

    k2mem --db $DBNAME seqs.fa

in both cases output will be sent to standard output by default.

To get a full list of options, use  `k2mem --help`.

References
----------
[Improving Metagenomic Classification using discriminative k-mers from sequencing data (In submission)]()
[Kraken 2 webpage](https://ccb.jhu.edu/software/kraken2/)  
[Kraken 2 manual](https://ccb.jhu.edu/software/kraken2/index.shtml?t=manual)