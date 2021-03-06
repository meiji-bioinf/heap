Heap
===============

Recent availability of large scale genomic resources enables us to conduct so called genome-wide association studies (GWAS) and genomic prediction (GP) studies, particularly with next-generation sequencing (NGS) data. The effectiveness of GWAS and GP depends on not only their mathematical models, but the quality and quantity of variants employed in the analysis. In NGS single nucleotide polymorphism (SNP) calling, conventional tools ideally require more reads for higher SNP sensitivity and accuracy. In this study, we aimed to develop a tool, Heap, that enables robustly sensitive and accurate calling of SNPs, particularly with a low coverage NGS data, which must be aligned to the reference genome sequences in advance. To reduce false positive SNPs, Heap determines genotypes and calls SNPs at each site except for sites at the both end of reads or containing a minor allele supported by only one read. Performance comparison with existing tools showed that Heap achieved the highest F-scores with low coverage (7X) restriction-site associated DNA sequencing reads of sorghum and rice individuals. This will facilitate cost-effective GWAS and GP studies in this NGS era. Code and documentation of Heap are freely available from https://github.com/meiji-bioinf/heap and our web site (http://bioinf.mind.meiji.ac.jp/lab/en/tools.html).

## 1. Version

	0.8.0

## 2. Algorithm

We designed Heap to identify SNPs from short read sequences of diploid species. In Heap analysis, short read sequences must be aligned to reference genome sequences in advance, and information on aligned reads, which is stored in either Sequence Alignment/MAP (SAM) format files or the binary version of [SAM (BAM) format files](https://samtools.github.io/hts-specs/SAMv1.pdf), must be employed.

After importing information on read alignments from a SAM or BAM file, Heap performs read filtering to obtain high quality reads. By default setting of Heap, reads with a phred scaled mapping quality score (MAPQ) below 20 are removed. Bases with a phred scaled quality score in base calling below 13 are also eliminated from the search scope of valid SNP sites. Heap also trims both ends of each read before mining SNPs, because it is empirically observed that these regions contain many base calling errors. By default setting, both ends with 2bp are not counted for SNP searches. If both ends of reads are trimmed in advance, please set option “-e 0” in Heap analysis to retain bases in both ends of reads. Moreover, flanking regions within 5bp of each INDEL site are also removed in SNP calling.

Next, Heap genotypes within the determined high quality region in each sample. On each nucleotide site, the allele frequency is calculated from the number of nucleotide bases (A, T, C or G) aligned on it. Heap ignores any nucleotide sites with equal to or more than 3 allele options. To determine the zygosity of each allele, a binomial test with allele frequency is performed (the null hypothesis H<sub>0</sub>: the allele is heterozygous). When the _P_ value of the binomial test is less than 0.05, the null hypothesis will be rejected and it is determined to be homozygous. Conversely, when the _P_ value is equal to or more than 0.05 and the minor allele is supported by equal to or more than 2 short reads, it is determined to be heterozygous. If neither is the case, the genotype will be undetermined.

Heap then performs SNP calling by comparing the genotypes between the sample (e.g. an inbred line) and the reference genome. The information on all SNPs between the sample and the reference genome is stored in a [Variant Call Format (VCF)](http://www.internationalgenome.org/wiki/Analysis/variant-call-format/) file. Finally, to determine SNPs among all samples, the VCF files for all samples are merged in a single VCF file by [BCFtools](https://github.com/samtools/bcftools/).

## 3. OS

Heap was tested on CentOS 6.6, Fedora 21, Ubuntu 15.04 and Mac OS X yosemite.

## 4. Docker image

A Docker image [centos7_heap_v0.8.0_dockerImage.tar.gz](http://bioinf.mind.meiji.ac.jp/lab/en/download/centos7_heap_v0.8.0_dockerImage.tar.gz) (216 MB) of heap on CentOS7 with required tools is available. This docker image enables you to use heap easily without installing requeired tools and heap. In advance, please install Docker on your machine according to [Docker offical web site](https://www.docker.com/). Docker is available not only on Linux OS but also MacOS and Windows10.

### i. Load the image to Docker

In advance load the image, please uncompress the image file as below.

```
$ gunzip centos7_heap_v0.8.0_dockerImage.tar.gz
```

The uncompressed image is able to load to Docker as below.

```
$ docker load < centos7_heap_v0.8.0_dockerImage.tar
```

### ii. Create and login to a container

To create a container from the image and login to the container, please execute `docker run` as below.

```
$ docker run -it centos7/heap:v0.8.0 /bin/sh
```

To refere a directory on your host machine including your data from a directory on the container, execute `docker run` with `-v` option as below.

```
$ docker run -v /Users/mkobayashi/Desktop/heap-0.8.0/testData:/testData -it centos7/heap:v0.8.0 /bin/sh
```

By the command, a directory `/Users/mkobayashi/Desktop/heap-0.8.0/testData` on the host machine will be mounted to `/testData` on the container.

After the login to the container, you are able to call SNPs by using heap as described in follow sections.

To login to the already exists container, check the id of the container by `docker ps -a`, start the container by `docker start`, and login to the container by `docker attach` as below.

```
$ docker ps -a
CONTAINER ID        IMAGE                     COMMAND             CREATED             STATUS                     PORTS               NAMES
00d873155a28        centos7/heap:v0.8.0       "/bin/sh"           2 hours ago         Exited (0) 6 seconds ago                       unruffled_rosalind
$ docker start 00d873155a28
$ docker attach 00d873155a28
```

## 5. Required tools

### i. [Boost C++ Libraries](http://www.boost.org/)

If boost libraries are not installed in your machine, please install boost libraries as below.

#### Installing boost for CentOS and Fedora

	$ sudo yum install -y boost-devel

#### Installing boost for Ubuntu

	$ sudo apt-get install -y libboost-all-dev

#### Installing boost for OS X

	$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	$ brew install boost

### ii. [HTSlib](https://github.com/samtools/htslib/) (version 1.1 or more)

Heap use `bgzip` and `tabix` commands of HTSlib to compress and index VCFs.

### iii. [BCFtools](https://github.com/samtools/bcftools/) (version 1.1 or more)

Heap use a `merge` command of BCFtools to merge raw VCFs, which are created by Heap with each BAM file.

Heap also use a `view` command of BCFtools to drop off allele count < 1 and trim alternate alleles not seen in subset.

## 6. Install

Download heap-0.8.0.tar.gz and decompress the tarball.

	$ tar xzvf heap-0.8.0.tar.gz
	$ cd heap-0.8.0

Then, configure by `./configure`.

	$ ./configure

If HTSlib had been installed to your specified prefix, execute `./configure` and `make` with `LDFLAGS` and `CPPFLAGS` as follows.

	$ ./configure \
	  LDFLAGS="-Wl,-rpath -Wl,/path/to/htslib-1.3.1/lib/ -L/path/to/htslib-1.3.1/lib/" \
	  CPPFLAGS="-I/path/to/htslib-1.3.1/include/"
	$ make \
	  LDFLAGS="-Wl,-rpath -Wl,/path/to/htslib-1.3.1/lib/ -L/path/to/htslib-1.3.1/lib/" \
	  CPPFLAGS="-I/path/to/htslib-1.3.1/include/"

If compilation is failed with error massage such as `cannot find -lboost_thread`, please try `make` with `LIBS` as follows.

	$ make \
	  LDFLAGS="-Wl,-rpath -Wl,/path/to/htslib-1.3.1/lib/ -L/path/to/htslib-1.3.1/lib/" \
	  CPPFLAGS="-I/path/to/htslib-1.3.1/include/" \
	  LIBS="-lboost_system -lboost_thread-mt -lboost_program_options -lhts"

Finally, install heap by `sudo make install`

	$ sudo make install

## 7. Usage

If HTSlib and/or BCFtools had been installed to your specified prefix, add path of HTSlib and/or BCFtools previously execute Heap as follows.

	$ export PATH=/path/to/bcftools/bin/:$PATH
	$ export PATH=/path/to/htslib/bin/:$PATH

Please execute Heap with -h for an operation check.

```

$ ./heap -h
/usr/bin/bgzip
/usr/bin/tabix
/usr/bin/bcftools
bcftools version 1.3.1
Heap version 0.8.0 options. Default values are presented in '()'.:
  -v [ --version ]                      Show version
  -h [ --help ]                         show help
  -r [ --ref ] arg                      Reference sequences used for the
                                        mapping in FASTA format
  -i [ --in_files ] arg                 Aligned reads in BAM or SAM format
                                        which must be sorted
  -o [ --out_file ] arg                 Prefix of output VCF file
  -m [ --min_mapq ] arg (=20)           Minimum MAPQ value
  -b [ --min_base_qual ] arg (=13)      Minimum phred scaled base quality score
  -d [ --min_depth ] arg (=3)           Minimum read depth
  -e [ --del_end_length ] arg (=2)      Deletion length at the both ends of
                                        reads (for RAD-Seq, 2 is recommended)
  -l [ --ignore_indel_length ] arg (=5) Length of INDEL flanking regions to
                                        ignore
  -t [ --thread_num ] arg (=1)          Number of threads
  -p [ --p_val ] arg (=0.0500000007)    P-value for binomial test in genotyping

```

In this version of Heap, BAM or SAM created by [Burrows-Wheeler Aligner(BWA)](http://bio-bwa.sourceforge.net/index.shtml) is only supported.

BAM or SAM must be sorted previously with the tools such as [SAMtools](http://www.htslib.org/) or [Picard Tools](http://broadinstitute.github.io/picard/).

## 8. Examples

### i. Test data

There is a test data in 'testData' directory.

```
Sbicolor_v2.1_255_Chr01_1-1000000.fa    # A genome sequence of chromosome 1 of Sbicolor_v2.1 between position 1 to 1,000,000.
GULUM_ABIAD.bam                         # Mapped RAD-seq reads obtained from GULUM_ABIAD.
RTx430.bam                              # Mapped RAD-seq reads obtained from RTx430.
SOR_1.bam                               # Mapped RAD-seq reads obtained from GULUM_ABIAD SOR_1.
```

### ii. SNP calling with the test data

To call SNPs with one sample simply with the test data, please execute `heap` as follows.

	$ heap -r Sbicolor_v2.1_255_Chr01_1-1000000.fa -i GULUM_ABIAD.bam -o snp

Then, Heap will output SNPs in [VCF (Variant Call Format) version 4.1](http://www.1000genomes.org/wiki/analysis/variant%20call%20format/vcf-variant-call-format-version-41) (snp.vcf.gz).

To call SNPs with multiple samples, please execute `heap` as follows.

	$ heap -r Sbicolor_v2.1_255_Chr01_1-1000000.fa -i GULUM_ABIAD.bam -i RTx430.bam -i SOR_1.bam -o snp

### iii. Result files of SNP calling with the test data

There are result files from SNP call with the test data in 'testResults' directory.

```
bcftools_version.txt               # Version of BCFtools used.
GULUM_ABIAD.bam.raw.vcf.log        # A log file of genotyping with GULUM_ABIAD.bam.
RTx430.bam.raw.vcf.log             # A log file of genotyping with RTx430.bam.
SOR_1.bam.raw.vcf.log              # A log file of genotyping with SOR_1.bam.
GULUM_ABIAD.bam.raw.vcf.gz         # A compressed genotype data in each site with GULUM_ABIAD.bam.
GULUM_ABIAD.bam.raw.vcf.gz.tbi     # An index of GULUM_ABIAD.bam.raw.vcf.gz.
RTx430.bam.raw.vcf.gz              # A compressed genotype data in each site with RTx430.bam.
RTx430.bam.raw.vcf.gz.tbi          # An index of RTx430.bam.raw.vcf.gz.
SOR_1.bam.raw.vcf.gz               # A compressed genotype data in each site with SOR_1.bam.
SOR_1.bam.raw.vcf.gz.tbi           # An index of SOR_1.bam.raw.vcf.gz.
snp.raw.vcf.gz                     # A compressed genotype data in each site with all samples.
snp.vcf.gz                         # A compressed SNP data in each site with all samples.
```
