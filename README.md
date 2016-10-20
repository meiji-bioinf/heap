Heap
===============

Recent availability of large scale genomic resources enables us to conduct so called genome-wide association studies (GWAS) and genomic prediction (GP) studies, particularly with next-generation sequencing (NGS) data. The effectiveness of GWAS and GP depends on not only their mathematical models, but the quality and quantity of variants employed in the analysis. In NGS single nucleotide polymorphism (SNP) calling, conventional tools ideally require more reads for higher SNP sensitivity and accuracy. In this study, we aimed to develop a tool, ÅeHeapÅf, that enables robustly sensitive and accurate calling of SNPs, particularly with a low coverage NGS data. Heap calls SNPs from NGS reads, which are aligned to the reference genome sequences in advance. Performance comparison with existing tools showed that Heap achieved the highest F-scores with low coverage (7X) restriction-site associated DNA (RAD) sequencing reads of sorghum and rice individuals. This will facilitate cost-effective GWAS and GP studies in this NGS era. Heap code and documentation are freely available from https://github.com/meiji-bioinf/heap and our web site (http://bioinf.mind.meiji.ac.jp/lab/en/tools.html).

##1. Version
	0.7.8

##2. OS
Heap was tested on CentOS 6.6, Fedora 21, Ubuntu 15.04 and Mac OS X yosemite.

##3. Required tools

###i. [Boost C++ Libraries](http://www.boost.org/)

If boost libraries are not installed in your machine, please install boost libraries as below.

####Installing boost for CentOS and Fedora

	$ sudo yum install -y boost-devel

####Installing boost for Ubuntu

	$ sudo apt-get install -y libboost-all-dev

####Installing boost for OS X

	$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	$ brew install boost

###ii. [HTSlib](https://github.com/samtools/htslib/) (version 1.1 or more)
Heap use `bgzip` and `tabix` commands of HTSlib to compress and index VCFs.

###iii. [BCFtools](https://github.com/samtools/bcftools/) (version 1.1 or more)
Heap use a `merge` command of BCFtools to merge raw VCFs, which are created by Heap with each BAM file.
Heap also use a `view` command of BCFtools to drop off allele count < 1 and trim alternate alleles not seen in subset.

##4. Install

Download heap-0.7.8.tar.gz and decompress the tarball.

	$ tar xzvf heap-0.7.8.tar.gz
	$ cd heap-0.7.8

Then, configure by `./configure`.

	$ ./configure

If HTSlib had been installed to your specified prefix, execute `./configure` and `make` with `LDFLAGS` and `CPPFLAGS` as follows.

	$ ./configure \
	  LDFLAGS="-Wl,-rpath -Wl,/path/to/htslib-1.2.1/lib/ -L/path/to/htslib-1.2.1/lib/" \
	  CPPFLAGS="-I/path/to/htslib-1.2.1/include/"
	$ make \
	  LDFLAGS="-Wl,-rpath -Wl,/path/to/htslib-1.2.1/lib/ -L/path/to/htslib-1.2.1/lib/" \
	  CPPFLAGS="-I/path/to/htslib-1.2.1/include/"

If compilation is failed with error massage such as `cannot find -lboost_thread`, please try `make` with `LIBS` as follows.

	$ make \
	  LDFLAGS="-Wl,-rpath -Wl,/path/to/htslib-1.2.1/lib/ -L/path/to/htslib-1.2.1/lib/" \
	  CPPFLAGS="-I/path/to/htslib-1.2.1/include/" \
	  LIBS="-lboost_system -lboost_thread-mt -lboost_program_options -lhts"

Finally, install heap by `sudo make install`

	$ sudo make install

##5. Usage

If HTSlib and/or BCFtools had been installed to your specified prefix, add path of HTSlib and/or BCFtools previously execute Heap as follows.

	$ export PATH=/path/to/bcftools/bin/:$PATH
	$ export PATH=/path/to/htslib/bin/:$PATH

Please execute Heap with -h for an operation check.

	$ heap -h
	/usr/local/bin/bgzip
	/usr/local/bin/tabix
	/usr/local/bin/bcftools
	bcftools version 1.2
	options:
	  -v [ --version ]                      Show version
	  -h [ --help ]                         show help
	  -r [ --ref ] arg                      Reference sequences had been used for 
	                                        the mapping in FASTA format
	  -i [ --in_files ] arg                 Aligned reads in BAM or SAM format 
	                                        which must be sorted
	  -o [ --out_file ] arg                 Prefix of output VCF file
	  -m [ --min_mapq ] arg (=20)           Minimum of MAPQ
	  -b [ --min_base_qual ] arg (=13)      Minimum of phred scaled base quality 
	                                        score
	  -d [ --min_depth ] arg (=3)           Minimum of read depth
	  -e [ --del_end_length ] arg (=2)      Deletion length at the both ends of 
	                                        reads (for RAD-Seq, 2 is recommended)
	  -l [ --ignore_indel_length ] arg (=5) Ignoring length of region neighboring 
	                                        INDELs
	  -t [ --thread_num ] arg (=1)          Number of threads
	  -p [ --p_val ] arg (=0.0500000007)    P-value for Chi-squared test in 
	                                        genotyping

In this version of Heap, BAM or SAM created by [Burrows-Wheeler Aligner(BWA)](http://bio-bwa.sourceforge.net/index.shtml) is only supported.
BAM or SAM must be sorted previously with the tools such as [SAMtools](http://www.htslib.org/) or [Picard Tools](http://broadinstitute.github.io/picard/).

There is a test data in 'testData' directory.
To call SNPs with one sample simply with the test data, please execute `heap` as follows.

	$ heap -r Sbicolor_v2.1_255_Chr01_1-1000000.fa -i GULUM_ABIAD.bam -o snp

Then, Heap will output SNPs in VCF format (snp.vcf.gz).
[VCF (Variant Call Format) version 4.1](http://www.1000genomes.org/wiki/analysis/variant%20call%20format/vcf-variant-call-format-version-41)

To call SNPs with multiple samples, please execute `heap` as follows.

	$ heap -r Sbicolor_v2.1_255_Chr01_1-1000000.fa -i GULUM_ABIAD.bam -i RTx430.bam -i SOR_1.bam -o snp
