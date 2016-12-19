/*
 * heap.cpp
 *
 *  Created on: 2015/06/16
 *      Author: mkobayashi
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/tr1/unordered_map.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include "bam.h"

#define MAX_STRING 128

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace tr1;

string time(){
	struct tm *date;
	time_t now;
	int year, month, day;
	int hour, minute, second;
	time(&now);
	date = localtime(&now);
	year = date->tm_year + 1900;
	month = date->tm_mon + 1;
	day = date->tm_mday;
	hour = date->tm_hour;
	minute = date->tm_min;
	second = date->tm_sec;

	stringstream year_str;
	year_str.setf(std::ios::right);
	year_str.fill('0');
	year_str.width(4);
	year_str << year;
	string year2 = year_str.str();

	stringstream month_str;
	month_str.setf(std::ios::right);
	month_str.fill('0');
	month_str.width(2);
	month_str << month;
	string month2 = month_str.str();

	stringstream day_str;
	day_str.setf(std::ios::right);
	day_str.fill('0');
	day_str.width(2);
	day_str << day;
	string day2 = day_str.str();

	stringstream hour_str;
	hour_str.setf(std::ios::right);
	hour_str.fill('0');
	hour_str.width(2);
	hour_str << hour;
	string hour2 = hour_str.str();

	stringstream minute_str;
	minute_str.setf(std::ios::right);
	minute_str.fill('0');
	minute_str.width(2);
	minute_str << minute;
	string minute2 = minute_str.str();

	stringstream second_str;
	second_str.setf(std::ios::right);
	second_str.fill('0');
	second_str.width(2);
	second_str << second;
	string second2 = second_str.str();

	string result = year2 + "/" + month2 + "/" + day2 + " " + hour2 + ":" + minute2 + ":" + second2;

	return result;
}

string time_str(){
	struct tm *date;
	time_t now;
	int year, month, day;
	int hour, minute, second;
	time(&now);
	date = localtime(&now);
	year = date->tm_year + 1900;
	month = date->tm_mon + 1;
	day = date->tm_mday;
	hour = date->tm_hour;
	minute = date->tm_min;
	second = date->tm_sec;

	stringstream year_str;
	year_str.setf(std::ios::right);
	year_str.fill('0');
	year_str.width(4);
	year_str << year;
	string year2 = year_str.str();

	stringstream month_str;
	month_str.setf(std::ios::right);
	month_str.fill('0');
	month_str.width(2);
	month_str << month;
	string month2 = month_str.str();

	stringstream day_str;
	day_str.setf(std::ios::right);
	day_str.fill('0');
	day_str.width(2);
	day_str << day;
	string day2 = day_str.str();

	stringstream hour_str;
	hour_str.setf(std::ios::right);
	hour_str.fill('0');
	hour_str.width(2);
	hour_str << hour;
	string hour2 = hour_str.str();

	stringstream minute_str;
	minute_str.setf(std::ios::right);
	minute_str.fill('0');
	minute_str.width(2);
	minute_str << minute;
	string minute2 = minute_str.str();

	stringstream second_str;
	second_str.setf(std::ios::right);
	second_str.fill('0');
	second_str.width(2);
	second_str << second;
	string second2 = second_str.str();

	string result = year2 + "_" + month2 + "_" + day2 + "_" + hour2 + "_" + minute2 + "_" + second2;

	return result;
}

int string2int(const string& str){
	int rt;
	stringstream ss;
	ss << str;
	ss >> rt;
	return rt;
}

string char2string(char val){
	string str;
	stringstream ss;
	ss << val;
	ss >> str;
	return str;
}

string char2string2(char* val){
	string str;
	stringstream ss;
	ss << val;
	ss >> str;
	return str;
}

string int2string(int val){
	string str;
	stringstream ss;
	ss << val;
	ss >> str;
	return str;
}

char string2char(const string& str){
	char rt;
	stringstream ss;
	ss << str;
	ss >> rt;
	return rt;
}

char* string2char2(const string& str){
	int len = str.length();
	char* rt = new char[len+1];
	memcpy(rt, str.c_str(), len+1);
	return rt;
}

string float2string(float val){
	string str;
	stringstream ss;
	ss << val;
	ss >> str;
	return str;
}

string double2string(double val){
	string str;
	stringstream ss;
	ss << val;
	ss >> str;
	return str;
}

string convSec(double sec){
	char str[10];
	if(sec >= 31536000){
		sprintf(str, "%.1fy", (sec / 60 / 60 / 24 / 365));
	}else if(sec < 31536000 && sec >= 604800){
		sprintf(str, "%.1fw", (sec / 60 / 60 / 24 / 7));
	}else if(sec < 604800 && sec >= 86400){
		sprintf(str, "%.1fd", (sec / 60 / 60 / 24));
	}else if(sec < 86400 && sec >= 3600){
		sprintf(str, "%.1fh", (sec / 60 / 60));
	}else if(sec < 3600 && sec >= 60){
		sprintf(str, "%.1fm", (sec / 60));
	}else{
		sprintf(str, "%.1fs", sec);
	}
	string rt;
	stringstream ss;
	ss << str;
	ss >> rt;
	return rt;
}

string Replace( string String1, string String2, string String3 )
{
    string::size_type  Pos( String1.find( String2 ) );

    while( Pos != string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }

    return String1;
}

string removeFilePath(string str){
	string rt = str;
	while(rt.find("/") != string::npos){
		rt = rt.substr((rt.find("/") + 1),(rt.length() - rt.find("/")));
	}
	return rt;
}

class Heap{
private:
	int min_mapq; // minimum of MAPQ
	int min_base_qual; // minimum of base quality
	int del_end_length; // length for deletion at both ends of reads
	int ignore_indel_length; // ignoring length of region neighboring INDELs
	unsigned int min_depth; // minimum depth each pos
	char* in_file_name; // input file name
	char* out_file_name; // output file name
    string ref_file; // reference file name
	unordered_map<string, string> ref_map; // reference sequences

	/* variables for BAM */
	bamFile bam_fh; // Prepare BAM file handler
	map<uint, string> chr; // Prepare container for integer ID of chromosome name
	bam_header_t *bamh; // Prepare BAM header
	int bytes_read; // Integer for judge read existence
	bam1_t *aln; // BAM alignment

	/* SAM variables */
	string rname; // chromosome name (rname)
	int pos; // position
	int flag; // FLAG
	int mapq; // MAPQ
	string cigar; // CIGAR
	int x0; // x0 (aux tag)
	int x1; // x1 (aux tag)
	string mdz; // mdz (aux tag)
	string seq; // alignment sequence
	string qual; // base quality
	string seq_tmp; // processed alignment sequence
	string qual_tmp; // processed base quality

	unordered_map<string, unordered_map<int, int> > indel; // regions neighboring indels
	map<string, map<int, string> > seq_pile; // pileup sequences

	float x2_1; // the x2 value for chi-squared test

	string heap_command; // commands of heap
	string ref_vcf; // vcf records to output
public:
    void set(int num1, int num2, int num3, int num4, int num5, char* inf, char* ouf, float flo1, string str1, string rfn);
    void read_ref(); // read reference sequence
	vector<int> convFlag(); // convert FLAGs
	int checkErrFlags(); // check error FLAGs
	string getCigarStrForBam(); // get CIGAR
	int checkBadCigar(); // check bad CIGAR
	void getAuxTagsForBAM(); // get aux tags (x0, x1 and mdz) for BAM alignment
	void getAuxTagsForSAM(vector<string> record); // get aux tags (x0, x1 and mdz) for SAM alignment
	int checkUniqMap(); // check uniq alignment
	string getSeqStrForBam(); // get alignment sequence
	string getQualStrForBam(); // get base quality
	void delSeqEnds(); // delete both ends of seq
	void markNeiIndels(); // mark regions neighboring INDELs
	void pileup(); // pileup sequences
	vector<string> convVcf(string chr, int pos, string seq); // convert pileup to VCF
	string chiTestForGeno(float ad1, float ad2, float ad1loc, float ad2loc);
	void getNextAlnForBAM(); // Get next read alignment data
	void cleanVariablesForSAM(); // clean variables for the next sam record
	void printVcf(); // print VCF
	void printRemainedVcf(); // print remained VCF
	void run();
};
void Heap::set(int num1, int num2, int num3, int num4, int num5, char* inf, char* ouf, float flo1, string str1, string rfn){
	min_mapq = num1;
	min_base_qual = num2;
	del_end_length = num3;
	ignore_indel_length = num4;
	min_depth = num5;
	in_file_name = inf;
	out_file_name = ouf;
	x2_1 = flo1;
	heap_command = str1;
	ref_file = rfn;
}
void Heap::read_ref(){
	// open reference.fasta file
	ifstream ifs_ref_file(string2char2(ref_file));
	if(ifs_ref_file.fail()){
			cerr << "File " << ref_file << " do not exist.\n";
			exit(0);
	}

	// get reference.fasta and prepare infomation of reference sequences for VCF
	ref_vcf = "##reference=file:" + removeFilePath(ref_file) + "\n";
	string line;
	string head;
	while(getline(ifs_ref_file, line)){
		if(line[0] == '>'){
			if(ref_vcf.find("contig") != string::npos){
				ref_vcf += ",length=" + int2string(ref_map[head].length()) + ">\n";
			}
			head = Replace(line, ">", "");
			ref_vcf += "##contig=<ID=" + head;
		}else{
			if(ref_map[head].length() == 0){
				ref_map[head] = line;
			}else{
				ref_map[head] += line;
			}
		}
	}
	ref_vcf += ",length=" + int2string(ref_map[head].length()) + ">\n";
	ifs_ref_file.close();
}
vector<int> Heap::convFlag(){
	vector<int> flags;
	int flag_tmp;
	flag_tmp = flag;
	if((flag_tmp - 2048) >= 0){ // 0. supplementary alignment
		flag_tmp = flag_tmp - 2048;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 1024) >= 0){ // 1. PCR or optical duplicate
		flag_tmp = flag_tmp - 1024;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 512) >= 0){ // 2. not passing quality controls
		flag_tmp = flag_tmp - 512;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 256) >= 0){ // 3. secondary alignment
		flag_tmp = flag_tmp - 256;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 128) >= 0){ // 4. the last segment in the template
		flag_tmp = flag_tmp - 128;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 64) >= 0){ // 5. the first segment in the template
		flag_tmp = flag_tmp - 64;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 32) >= 0){ // 6. SEQ of the next segment in the template being reversed
		flag_tmp = flag_tmp - 32;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 16) >= 0){ // 7. SEQ being reverse complemented
		flag_tmp = flag_tmp - 16;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 8) >= 0){ // 8. next segment in the template unmapped
		flag_tmp = flag_tmp - 8;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 4) >= 0){ // 9. segment unmapped
		flag_tmp = flag_tmp - 4;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 2) >= 0){ // 10. each segment properly aligned according to the aligner
		flag_tmp = flag_tmp - 2;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	if((flag_tmp - 1) >= 0){ // 11. template having multiple segments in sequencing
		flag_tmp = flag_tmp - 1;
		flags.push_back(1);
	}else{
		flags.push_back(0);
	}
	return flags;
}
int Heap::checkErrFlags(){
	vector<int> flags = convFlag();
	if(
			flags[0] == 1 || // 0. supplementary alignment
			flags[1] == 1 || // 1. PCR or optical duplicate
			flags[2] == 1 || // 2. not passing quality controls
			flags[3] == 1 || // 3. secondary alignment
			flags[9] == 1    // 9. segment unmapped
		){
		return 1;
	}else{
		return 0;
	}
}
string Heap::getCigarStrForBam(){
	string cigar = "";
	int  cigar_ci, cigar_len;
	uint32_t *cigar_t = bam1_cigar(aln);
	for (int k = 0; k < aln->core.n_cigar; k++) {
		cigar_ci  = cigar_t[k] & BAM_CIGAR_MASK;
		cigar_len = cigar_t[k] >> BAM_CIGAR_SHIFT;
		cigar += int2string(cigar_len);
		switch(cigar_ci) {
			case BAM_CMATCH:
				cigar += "M";
				break;
			case BAM_CINS:
				cigar += "I";
				break;
			case BAM_CDEL:
				cigar += "D";
				break;
			case BAM_CREF_SKIP:
				cigar += "N";
				break;
			case BAM_CSOFT_CLIP:
				cigar += "S";
				break;
			case BAM_CHARD_CLIP:
				cigar += "H";
				break;
			case BAM_CPAD:
				cigar += "P";
				break;
        }
	}
	return cigar;
}
int Heap::checkBadCigar(){
	if(
		cigar.find('N') != string::npos ||
		cigar.find('S') != string::npos ||
		cigar.find('H') != string::npos ||
		cigar.find('P') != string::npos ||
		cigar.find('=') != string::npos ||
		cigar.find('X') != string::npos
	){
		return 1;
	}else{
		return 0;
	}

}
void Heap::getAuxTagsForBAM(){
	int i = 0;
	uint8_t *aux = bam_get_aux(aln);
	x0 = -1;
	x1 = -1;
	mdz = "";
	while(i < bam_get_l_aux(aln)){
		char tag[100];
		sprintf(tag, "%.2s", aux+i);
		string tag_str = char2string2(tag);
		i += 2;
		// get X0 tag
		if(tag_str[0] == 'X' && tag_str[1] == '0'){
			x0 = bam_aux2i(aux+i);
		}
		// get X1 tag
		if(tag_str[0] == 'X' && tag_str[1] == '1'){
			x1 = bam_aux2i(aux+i);
		}
		// get MD tag
		if(tag_str[0] == 'M' && tag_str[1] == 'D'){
			switch (*(aux+i)) {
				case 'Z':
					while(*(aux+1+i) != '\0'){
						mdz += *(aux+1+i);
						++i;
					}
					break;
			}
		}
		i++;i++;
	}
}
void Heap::getAuxTagsForSAM(vector<string> record){
	x0 = 0;
	x1 = 0;
	mdz = "";
	for(unsigned int i = 11; i < record.size(); i++){
		if(
			record[i][0] == 'M' &&
			record[i][1] == 'D' &&
			record[i][3] == 'Z'
		){
			mdz = Replace(record[i], "MD:Z:", "");
		}else if(
				record[i][0] == 'X' &&
				record[i][1] == '0'
		){
				x0 = string2int(Replace(record[i], "X0:i:", ""));
		}else if(
				record[i][0] == 'X' &&
				record[i][1] == '1'
		){
				x1 = string2int(Replace(record[i], "X1:i:", ""));
		}
	}
}
int Heap::checkUniqMap(){
	if(x0 >= 0 && x1 >= 0){
		if(x0 == 1 && x1 == 0){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}
string Heap::getSeqStrForBam(){
	string seq;
	uint8_t j;
	for (int i = 0; i < aln->core.l_qseq; i++) {
		j = bam1_seqi(bam1_seq(aln), i);
		switch(j) {
		case 1:
			seq += 'A';
			break;
		case 2:
			seq += 'C';
			break;
		case 4:
			seq += 'G';
			break;
		case 8:
			seq += 'T';
			break;
		case 15:
			seq += 'N';
			break;
		}
	}
	return seq;
}
string Heap::getQualStrForBam(){
	string qual;
	uint8_t *q = bam1_qual(aln);
	for (int i = 0; i < aln->core.l_qseq; i++) {
		qual += char(int(q[i]) + 33);
	}
	return qual;
}
void Heap::delSeqEnds(){
	seq_tmp = seq;
	qual_tmp = qual;
	int test_flag = 0;
	if(del_end_length > 0){
		string cigar_int_str;
		vector<string> cigar_vec;
		for(unsigned int i = 0; i < cigar.size(); i++){
			if(cigar[i] != 'M' && cigar[i] != 'D' && cigar[i] != 'I'){
				cigar_int_str += char2string(cigar[i]);
			}else{
				cigar_vec.push_back((cigar_int_str + cigar[i]));
				cigar_int_str = "";
			}
		}
		int del_end_length_tmp = del_end_length;
		unsigned int i = 0;
		while(del_end_length_tmp > 0){
			vector<string>::iterator it1 = cigar_vec.begin();
			string cigar_int_str(&cigar_vec[i][0], &cigar_vec[i][(cigar_vec[i].length() - 1)]);
			string cigar_char_str = char2string(cigar_vec[i][(cigar_vec[i].length() - 1)]);
			if(string2int(cigar_int_str) > del_end_length_tmp){
				if(cigar_char_str == "M"){
					pos = pos + del_end_length_tmp;
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}else if(cigar_char_str == "D"){
					pos = pos + del_end_length_tmp;
				}else if(cigar_char_str == "I"){
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}
				cigar_vec[i] = int2string( string2int(cigar_int_str) - del_end_length_tmp ) + cigar_char_str;
				del_end_length_tmp = del_end_length_tmp - del_end_length_tmp;
				break;
			}else if(string2int(cigar_int_str) == del_end_length_tmp){
				if(cigar_char_str == "M"){
					pos = pos + del_end_length_tmp;
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}else if(cigar_char_str == "D"){
					pos = pos + del_end_length_tmp;
				}else if(cigar_char_str == "I"){
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}
				cigar_vec.erase(it1);
				del_end_length_tmp = del_end_length_tmp - del_end_length_tmp;
				i--;
				break;
			}else if(string2int(cigar_int_str) < del_end_length_tmp){
				if(cigar_char_str == "M"){
					pos = pos + string2int(cigar_int_str);
					seq_tmp.erase(0, string2int(cigar_int_str));
					qual_tmp.erase(0, string2int(cigar_int_str));
				}else if(cigar_char_str == "D"){
					pos = pos + string2int(cigar_int_str);
				}else if(cigar_char_str == "I"){
					seq_tmp.erase(0, string2int(cigar_int_str));
					qual_tmp.erase(0, string2int(cigar_int_str));
				}
				cigar_vec.erase(it1);
				del_end_length_tmp = del_end_length_tmp - string2int(cigar_int_str);
				i--;
			}
			i++;
		}

		if(char2string(cigar_vec[0][(cigar_vec[0].length() - 1)]) == "I"){
			string cigar_int_str(&cigar_vec[0][0], &cigar_vec[0][(cigar_vec[0].length() - 1)]);
			seq_tmp.erase(0, string2int(cigar_int_str));
			qual_tmp.erase(0, string2int(cigar_int_str));
			vector<string>::iterator it1 = cigar_vec.begin();
			cigar_vec.erase(it1);
		}else if(char2string(cigar_vec[0][(cigar_vec[0].length() - 1)]) == "D"){
			string cigar_int_str(&cigar_vec[0][0], &cigar_vec[0][(cigar_vec[0].length() - 1)]);
			pos = pos + string2int(cigar_int_str);
			vector<string>::iterator it1 = cigar_vec.begin();
			cigar_vec.erase(it1);
		}

		reverse(cigar_vec.begin(), cigar_vec.end());
		reverse(seq_tmp.begin(), seq_tmp.end());
		reverse(qual_tmp.begin(), qual_tmp.end());

		del_end_length_tmp = del_end_length;
		i = 0;
		while(del_end_length_tmp > 0){
			vector<string>::iterator it1 = cigar_vec.begin();
			string cigar_int_str(&cigar_vec[i][0], &cigar_vec[i][(cigar_vec[i].length() - 1)]);
			string cigar_char_str = char2string(cigar_vec[i][(cigar_vec[i].length() - 1)]);
			if(test_flag == 1){
				cout << i << "\t" << cigar_int_str << cigar_char_str << endl;
			}
			if(string2int(cigar_int_str) > del_end_length_tmp){
				if(cigar_char_str == "M"){
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}else if(cigar_char_str == "D"){
				}else if(cigar_char_str == "I"){
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}
				cigar_vec[i] = int2string( string2int(cigar_int_str) - del_end_length_tmp ) + cigar_char_str;
				del_end_length_tmp = del_end_length_tmp - del_end_length_tmp;
				break;
			}else if(string2int(cigar_int_str) == del_end_length_tmp){
				if(cigar_char_str == "M"){
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}else if(cigar_char_str == "D"){
				}else if(cigar_char_str == "I"){
					seq_tmp.erase(0, del_end_length_tmp);
					qual_tmp.erase(0, del_end_length_tmp);
				}
				cigar_vec.erase(it1);
				del_end_length_tmp = del_end_length_tmp - del_end_length_tmp;
				i--;
				break;
			}else if(string2int(cigar_int_str) < del_end_length_tmp){
				if(cigar_char_str == "M"){
					seq_tmp.erase(0, string2int(cigar_int_str));
					qual_tmp.erase(0, string2int(cigar_int_str));
				}else if(cigar_char_str == "D"){
				}else if(cigar_char_str == "I"){
					seq_tmp.erase(0, string2int(cigar_int_str));
					qual_tmp.erase(0, string2int(cigar_int_str));
				}
				cigar_vec.erase(it1);
				del_end_length_tmp = del_end_length_tmp - string2int(cigar_int_str);
				i--;
			}
			i++;
		}

		if(char2string(cigar_vec[0][(cigar_vec[0].length() - 1)]) == "I"){
			string cigar_int_str(&cigar_vec[0][0], &cigar_vec[0][(cigar_vec[0].length() - 1)]);
			seq_tmp.erase(0, string2int(cigar_int_str));
			qual_tmp.erase(0, string2int(cigar_int_str));
			vector<string>::iterator it1 = cigar_vec.begin();
			cigar_vec.erase(it1);
		}else if(char2string(cigar_vec[0][(cigar_vec[0].length() - 1)]) == "D"){
			vector<string>::iterator it1 = cigar_vec.begin();
			cigar_vec.erase(it1);
		}

		reverse(cigar_vec.begin(), cigar_vec.end());
		reverse(seq_tmp.begin(), seq_tmp.end());
		reverse(qual_tmp.begin(), qual_tmp.end());

		for(unsigned int i = 0; i < cigar_vec.size(); i++){
			if(i == 0){
				cigar = cigar_vec[i];
			}else{
				cigar += cigar_vec[i];
			}
		}

	}
}
void Heap::markNeiIndels(){
	string cigar_str;
	int cigar_int = 0;
	for(unsigned int i = 0; i < cigar.size(); i++){
		if(
			cigar[i] != 'M' &&
			cigar[i] != 'D' &&
			cigar[i] != 'I'
		){
			cigar_str += char2string(cigar[i]);
		}else{
			if(cigar[i] == 'I'){
				seq_tmp.erase(cigar_int, string2int(cigar_str));
				qual_tmp.erase(cigar_int, string2int(cigar_str));
				for(int j = 0; j < (ignore_indel_length * 2); j++){
					indel[rname][((pos - 1) + cigar_int - 1 - (ignore_indel_length - 1) + j)] = 1;
				}
			}else if(cigar[i] == 'D'){
				for(int j = 0; j < string2int(cigar_str); j++){
					seq_tmp.insert(cigar_int, "X" );
					qual_tmp.insert(cigar_int, "X" );
				}
				cigar_int = cigar_int + string2int(cigar_str);
				for(int j = 0; j < ((ignore_indel_length * 2) + string2int(cigar_str)); j++){
					indel[rname][((pos - 1) + (cigar_int - 1) - 1 - (ignore_indel_length - 1) - string2int(cigar_str) + j)] = 1;
				}
			}else if(cigar[i] == 'M'){
				cigar_int = cigar_int + string2int(cigar_str);
			}
			cigar_str = "";
		}
	}
}
void Heap::pileup(){
	for(unsigned int i = 0 + 1; i < (seq_tmp.length() - 1); i++){
		int qual_int = qual_tmp[i] - 33;
		if(qual_int >= min_base_qual && seq_tmp[i] != 'X'){
			if(indel[rname][(pos + i - 1)] > 0){
			}else{
				seq_pile[rname][(pos + i - 1)] += char2string(seq_tmp[i]);
			}
		}
	}
}
string Heap::chiTestForGeno(float ad1, float ad2, float ad1loc, float ad2loc){
	string GT = "NA";
	float e = (ad1 + ad2) / 2;
	float x2 = ( (ad1 - e) * (ad1 - e) / e ) + ( (ad2 - e) * (ad2 - e) / e );
	if(ad2 < 1){
		if(ad1loc == 0 && ad2loc == 1){
			GT = "0/0";
		}else if(ad1loc == 0 && ad2loc == 2){
			GT = "0/0";
		}else if(ad1loc == 0 && ad2loc == 3){
			GT = "0/0";
		}else if(ad1loc == 1 && ad2loc == 2){
			GT = "1/1";
		}else if(ad1loc == 1 && ad2loc == 3){
			GT = "1/1";
		}else if(ad1loc == 2 && ad2loc == 3){
			GT = "2/2";
		}
		return GT;
	}else if(ad1 < 1){
		if(ad1loc == 0 && ad2loc == 1){
			GT = "1/1";
		}else if(ad1loc == 0 && ad2loc == 2){
			GT = "2/2";
		}else if(ad1loc == 0 && ad2loc == 3){
			GT = "3/3";
		}else if(ad1loc == 1 && ad2loc == 2){
			GT = "2/2";
		}else if(ad1loc == 1 && ad2loc == 3){
			GT = "3/3";
		}else if(ad1loc == 2 && ad2loc == 3){
			GT = "3/3";
		}
		return GT;
	}else{
		if(x2 > x2_1 && ad1 > ad2){
			if(ad1loc == 0 && ad2loc == 1){
				GT = "0/0";
			}else if(ad1loc == 0 && ad2loc == 2){
				GT = "0/0";
			}else if(ad1loc == 0 && ad2loc == 3){
				GT = "0/0";
			}else if(ad1loc == 1 && ad2loc == 2){
				GT = "1/1";
			}else if(ad1loc == 1 && ad2loc == 3){
				GT = "1/1";
			}else if(ad1loc == 2 && ad2loc == 3){
				GT = "2/2";
			}
		}else if(x2 > x2_1 && ad1 < ad2){
			if(ad1loc == 0 && ad2loc == 1){
				GT = "1/1";
			}else if(ad1loc == 0 && ad2loc == 2){
				GT = "2/2";
			}else if(ad1loc == 0 && ad2loc == 3){
				GT = "3/3";
			}else if(ad1loc == 1 && ad2loc == 2){
				GT = "2/2";
			}else if(ad1loc == 1 && ad2loc == 3){
				GT = "3/3";
			}else if(ad1loc == 2 && ad2loc == 3){
				GT = "3/3";
			}
		}else{
			if(ad1 + ad2 < 10){
				if(ad1loc == 0 && ad2loc == 1 && ad1 > 1 && ad2 > 1){
					GT = "0/1";
				}else if(ad1loc == 0 && ad2loc == 2 && ad1 > 1 && ad2 > 1){
					GT = "0/2";
				}else if(ad1loc == 0 && ad2loc == 3 && ad1 > 1 && ad2 > 1){
					GT = "0/3";
				}else if(ad1loc == 1 && ad2loc == 2 && ad1 > 1 && ad2 > 1){
					GT = "1/2";
				}else if(ad1loc == 1 && ad2loc == 3 && ad1 > 1 && ad2 > 1){
					GT = "1/3";
				}else if(ad1loc == 2 && ad2loc == 3 && ad1 > 1 && ad2 > 1){
					GT = "2/3";
				}else{
					GT = "./.";
				}
			}else{
				if(ad1loc == 0 && ad2loc == 1){
					GT = "0/1";
				}else if(ad1loc == 0 && ad2loc == 2){
					GT = "0/2";
				}else if(ad1loc == 0 && ad2loc == 3){
					GT = "0/3";
				}else if(ad1loc == 1 && ad2loc == 2){
					GT = "1/2";
				}else if(ad1loc == 1 && ad2loc == 3){
					GT = "1/3";
				}else if(ad1loc == 2 && ad2loc == 3){
					GT = "2/3";
				}else{
					GT = "./.";
				}
			}
		}
		return GT;
	}
	return GT;
}
vector<string> Heap::convVcf(string chr, int pos, string seq){
	string ref = char2string(ref_map[chr][pos]);
	string GT = "NA";
	string EC = "NA";
	string alt = "NA";
	unordered_map<string, float> ad;
	for(unsigned int i = 0; i < seq.size(); i++){
		ad[char2string(seq[i])]++;
	}
	unordered_map<string, float>::iterator it_ad_find = ad.find(ref);
	if(it_ad_find == ad.end()){
		ad[char2string(ref_map[chr][pos])] = 0;
	}
	unordered_map<string, float>::iterator it_ad = ad.begin();
	while(it_ad != ad.end()){
		it_ad++;
	}
	if(ad.size() == 1){
		GT = "0/0";
		EC = ".";
		alt = ".";
	}else if(ad.size() == 2){
		float ad_ref = 0;
		float ad_ale = 0;
		unordered_map<string, float>::iterator it_ad_sort = ad.begin();
		while(it_ad_sort != ad.end()){
			if((*it_ad_sort).first == ref){
				ad_ref = (*it_ad_sort).second;
			}else{
				ad_ale = (*it_ad_sort).second;
				alt = (*it_ad_sort).first;
			}
			it_ad_sort++;
		}
		if(ad_ref != 0 && ad_ale == 0){
			GT = "0/0";
		}else if(ad_ref == 0 && ad_ale != 0){
			GT = "1/1";
		}else{
			GT = chiTestForGeno(ad_ref, ad_ale, 0, 1);
		}
		EC = float2string(ad_ale);
	}else if(ad.size() == 3){
		float ad_ref = 0;
		map<string, float> ad_ale;
		float ad_ale1 = 0;
		float ad_ale2 = 0;
		unordered_map<string, float>::iterator it_ad_sort = ad.begin();
		while(it_ad_sort != ad.end()){
			if((*it_ad_sort).first == ref){
				ad_ref = (*it_ad_sort).second;
			}else{
				ad_ale[(*it_ad_sort).first] = (*it_ad_sort).second;
			}
			it_ad_sort++;
		}
		map<string, float>::iterator it_ad_ale = ad_ale.begin();
		while(it_ad_ale != ad_ale.end()){
			if(ad_ale1 == 0){
				ad_ale1 = (*it_ad_ale).second;
				alt = (*it_ad_ale).first;
			}else{
				ad_ale2 = (*it_ad_ale).second;
				alt = alt + "," + (*it_ad_ale).first;
			}
			it_ad_ale++;
		}
		EC = float2string(ad_ale1) + "," + float2string(ad_ale2);
		if(ad_ref != 0 && ad_ale1 == 0 && ad_ale2 == 0){
			GT = "0/0";
		}else if(ad_ref == 0 && ad_ale1 != 0 && ad_ale2 == 0){
			GT = "1/1";
		}if(ad_ref == 0 && ad_ale1 == 0 && ad_ale2 != 0){
			GT = "2/2";
		}else{
			if(ad_ref == ad_ale1 && ad_ref == ad_ale2 && ad_ale1 == ad_ale2){
				GT = "./.";
			}else if(ad_ref == ad_ale1 && ad_ref > ad_ale2){
				GT = chiTestForGeno(ad_ref, ad_ale1, 0, 1);
			}else if(ad_ref == ad_ale2 && ad_ref > ad_ale1){
				GT = chiTestForGeno(ad_ref, ad_ale2, 0, 2);
			}else if(ad_ale1 == ad_ale2 && ad_ale1 > ad_ref){
				GT = chiTestForGeno(ad_ale1, ad_ale2, 1, 2);
			}else if(ad_ref == ad_ale1 && ad_ale2 > ad_ref){
				if(chiTestForGeno(ad_ref, ad_ale2, 0, 2) == chiTestForGeno(ad_ale1, ad_ale2, 1, 2)){
					GT = chiTestForGeno(ad_ref, ad_ale2, 0, 2);
				}else{
					GT = "./.";
				}
			}else if(ad_ref == ad_ale2 && ad_ale1 > ad_ref){
				if(chiTestForGeno(ad_ref, ad_ale1, 0, 1) == chiTestForGeno(ad_ale1, ad_ale2, 1, 2)){
					GT = chiTestForGeno(ad_ref, ad_ale1, 0, 1);
				}else{
					GT = "./.";
				}
			}else if(ad_ale1 == ad_ale2 && ad_ref > ad_ale1){
				if(chiTestForGeno(ad_ref, ad_ale1, 0, 1) == chiTestForGeno(ad_ref, ad_ale2, 0, 2)){
					GT = chiTestForGeno(ad_ref, ad_ale1, 0, 1);
				}else{
					GT = "./.";
				}
			}else{
				if(chiTestForGeno(ad_ref, ad_ale1, 0, 1) == chiTestForGeno(ad_ref, ad_ale2, 0, 2)){
					GT = chiTestForGeno(ad_ref, ad_ale1, 0, 1);
				}else if(chiTestForGeno(ad_ref, ad_ale1, 0, 1) == chiTestForGeno(ad_ale1, ad_ale2, 1, 2)){
					GT = chiTestForGeno(ad_ref, ad_ale1, 0, 1);
				}else if(chiTestForGeno(ad_ref, ad_ale2, 0, 2) == chiTestForGeno(ad_ale1, ad_ale2, 1, 2)){
					GT = chiTestForGeno(ad_ref, ad_ale2, 0, 2);
				}else if(chiTestForGeno(ad_ref, ad_ale1, 0, 1)[0] != chiTestForGeno(ad_ref, ad_ale1, 0, 1)[2]){
					GT = chiTestForGeno(ad_ref, ad_ale1, 0, 1);
				}else if(chiTestForGeno(ad_ref, ad_ale2, 0, 2)[0] != chiTestForGeno(ad_ref, ad_ale2, 0, 2)[2]){
					GT = chiTestForGeno(ad_ref, ad_ale2, 0, 2);
				}else if(chiTestForGeno(ad_ale1, ad_ale2, 1, 2)[0] != chiTestForGeno(ad_ale1, ad_ale2, 1, 2)[2]){
					GT = chiTestForGeno(ad_ale1, ad_ale2, 1, 2);
				}else{
					GT = "./.";
				}
			}
		}
		ad_ale.clear();
	}else if(ad.size() > 3){
		GT = "./.";
	}
	string data = "";
	string format = "";
	if(EC == "."){
		format = "GT:DP";
		data = GT + ":" + float2string(seq.length());
	}else{
		format = "GT:DP:EC";
		data = GT + ":" + float2string(seq.length()) + ":" + EC;
	}
	vector<string> result;
	result.push_back(alt);
	result.push_back(format);
	result.push_back(data);

	ad.clear();
	return result;

//	result.clear();
}
void Heap::printVcf(){
	ofstream vcf_ofs(out_file_name, ios::app);
	map<string, map<int, string> >::iterator pile_it1 = seq_pile.begin();
	while(pile_it1 != seq_pile.end()){
		map<int, string>::iterator pile_it2 = (*pile_it1).second.begin();
		while(pile_it2 != (*pile_it1).second.end()){
			if((rname == (*pile_it1).first && pos > (*pile_it2).first) || rname != (*pile_it1).first){
				if((*pile_it2).second.length() >= min_depth){
					vector<string> alt_and_data = convVcf((*pile_it1).first, (*pile_it2).first, (*pile_it2).second);
					if(alt_and_data[0].find("NA") == string::npos){
						vcf_ofs << (*pile_it1).first << "\t"
								<< int2string(((*pile_it2).first + 1)) << "\t"
								<< "." << "\t"
								<< ref_map[(*pile_it1).first][(*pile_it2).first] << "\t"
								<< alt_and_data[0] << "\t"
								<< "." << "\t"
								<< "." << "\t"
								<< "." << "\t"
								<< alt_and_data[1] << "\t"
								<< alt_and_data[2] << "\n";
					}
				}
				seq_pile[(*pile_it1).first].erase(pile_it2++);
			}else{
				pile_it2++;
			}
		}
		if(rname != (*pile_it1).first){
			seq_pile.erase(pile_it1++);
		}else{
			pile_it1++;
		}
	}
	vcf_ofs.close();
}
void Heap::printRemainedVcf(){
	ofstream vcf_ofs(out_file_name, ios::app);
	map<string, map<int, string> >::iterator pile_it1 = seq_pile.begin();
	while(pile_it1 != seq_pile.end()){
		map<int, string>::iterator pile_it2 = (*pile_it1).second.begin();
		while(pile_it2 != (*pile_it1).second.end()){
			if((*pile_it2).second.length() >= min_depth){
				vector<string> alt_and_data = convVcf((*pile_it1).first, (*pile_it2).first, (*pile_it2).second);
				if(alt_and_data[0].find("NA") == string::npos){
					vcf_ofs << (*pile_it1).first << "\t"
							<< int2string(((*pile_it2).first + 1)) << "\t"
							<< "." << "\t"
							<< ref_map[(*pile_it1).first][(*pile_it2).first] << "\t"
							<< alt_and_data[0] << "\t"
							<< "." << "\t"
							<< "." << "\t"
							<< "." << "\t"
							<< alt_and_data[1] << "\t"
							<< alt_and_data[2] << "\n";
				}
			}
			seq_pile[(*pile_it1).first].erase(pile_it2++);
		}
		seq_pile.erase(pile_it1++);
	}
	vcf_ofs.close();
}
void Heap::getNextAlnForBAM(){
	string rname;
	pos = 0;
	flag = 0;
	mapq = 0;
	cigar = "";
	x0 = -1;
	x1 = -1;
	mdz = "";
	seq = "";
	qual = "";
	seq_tmp = "";
	qual_tmp = "";
	indel.clear();
	bytes_read = bam_read1(bam_fh, aln);
}
void Heap::cleanVariablesForSAM(){
	string rname;
	pos = 0;
	flag = 0;
	mapq = 0;
	cigar = "";
	x0 = -1;
	x1 = -1;
	mdz = "";
	seq = "";
	qual = "";
	seq_tmp = "";
	qual_tmp = "";
	indel.clear();
}
void Heap::run(){
    
	// read reference sequence
    read_ref();

    // open alignment file
	ifstream ifs_in_file(in_file_name);
	if(ifs_in_file.fail()){
			cerr << "File " << in_file_name << " do not exist.\n";
			exit(0);
	}

	// write header of vcf
	ofstream vcf_ofs(out_file_name);
	vcf_ofs << "##fileformat=VCFv4.2" << endl;
	vcf_ofs << "##source=\"Heap v0.7.8\"" << endl;
	vcf_ofs << "##HeapCommand=" << heap_command;
	vcf_ofs << ref_vcf;
	vcf_ofs << "##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotype\">" << endl;
	vcf_ofs << "##FORMAT=<ID=DP,Number=1,Type=Integer,Description=\"Read Depth\">" << endl;
	vcf_ofs << "##FORMAT=<ID=EC,Number=A,Type=Integer,Description=\"Alternate Allele Counts\">" << endl;
	vcf_ofs << "#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT\t";
	vcf_ofs << removeFilePath(in_file_name) << endl;
	string rnamePre = "";
	vcf_ofs.close();

	// prepare log file name
	string vcf_log = char2string2(out_file_name) + ".log";
	ofstream ofs_vcf_log(string2char2(vcf_log));

	cout << "START: Heap::run " << in_file_name << " " << time() << endl;
	ofs_vcf_log << "START: Heap::run " << in_file_name << " " << time();
	ofs_vcf_log << endl;

	ofs_vcf_log << "Current_time\tProcessed_reads_count\tProcessing_site\tRemaining_time" << endl;

	if(char2string2(in_file_name).find(".bam") != string::npos){
		if(char2string2(in_file_name).substr(char2string2(in_file_name).find(".bam"),4) == ".bam"){

			// count reads
			bamFile bam_fh_tmp = bam_open(in_file_name, "r");
			bam_header_t *bamh_tmp = bam_header_init();
			bamh_tmp = bam_header_read(bam_fh_tmp);
			bam_header_destroy(bamh_tmp);
			bam1_t *aln_tmp = bam_init1();
			int bytes_read_tmp = 0;
			bytes_read_tmp = bam_read1(bam_fh_tmp, aln_tmp);
			double total_read_count = 0;
			while(bytes_read_tmp > 0){
				total_read_count++;
				bytes_read_tmp = bam_read1(bam_fh_tmp, aln_tmp);
			}
			bam_destroy1(aln_tmp);
			bam_close(bam_fh_tmp);

			// Get the BAM file handler
			bam_fh = bam_open(in_file_name, "r");

			// Get initial position of BAM header
			bamh = bam_header_init();

			// Get BAM header
			bamh = bam_header_read(bam_fh);

			// Record integer ID to container of chromosome name
			for (uint j = 0; j < (uint) bamh->n_targets; j++) {
				chr[j] = string(bamh->target_name[j]);
			}

			// Destroy BAM header
			bam_header_destroy(bamh);

			// Integer for judge read existence
			bytes_read = 0;

			// Set position initial alignment
			aln = bam_init1();

			// Get alignment data
			bytes_read = bam_read1(bam_fh, aln);

			// Get start time
			time_t start = time(0);

			int line_count = 0;
			while(bytes_read > 0){

		    	// get chromosome name (rname)
				rname = chr[aln->core.tid];
		    	if(line_count == 0){
		    		rnamePre = rname;
		    	}

		    	// get alignment position
		    	pos = (aln->core.pos + 1);

		    	line_count++;
				if(line_count % 100000 == 0 || rname != rnamePre){
					time_t now = time(0);
					ofs_vcf_log << time() << "\t";
					char log[256];
					sprintf(log, "%'d",line_count);
					ofs_vcf_log << log << "\t";
					ofs_vcf_log << rname << ":" << pos << "\t";
					ofs_vcf_log << convSec(((total_read_count - line_count) / (line_count / difftime(now, start)))) << endl;
					printVcf();
				}
				rnamePre = rname;
			
		    	// get FLAG
		    	flag = aln->core.flag;

				// check error FLAGs
		    	if(checkErrFlags() == 1){
		    		// Get next read alignment data
		    		getNextAlnForBAM();
		    		continue;
		    	}

		    	// get MAPQ
		    	mapq = aln->core.qual;

		    	// check MAPQ
				if(mapq < min_mapq){
					// Get next read alignment data
					getNextAlnForBAM();
					continue;
				}

		    	// get CIGAR
		    	cigar = getCigarStrForBam();

				// check bad CIGAR
		    	if(checkBadCigar() == 1){
					// Get next read alignment data
					getNextAlnForBAM();
					continue;
		    	}

				// get aux tags (x0, x1 and mdz)
		    	getAuxTagsForBAM();

				// check uniq alignment
				if(checkUniqMap() == 0){
					// Get next read alignment data
					getNextAlnForBAM();
					continue;
				}

		    	// get alignment sequence
				seq = getSeqStrForBam();

				// get base quality
				qual = getQualStrForBam();

				// delete both ends of seq
				delSeqEnds();

				// mark regions neighboring INDELs
				if(cigar.find('I') != string::npos || cigar.find('D') != string::npos){
					markNeiIndels();
				}

				// pileup sequences
				pileup();

				// Get next read alignment data
				getNextAlnForBAM();

		    }

			// close bam file handler
			bam_destroy1(aln);
			bam_close(bam_fh);
		}
	}else if(char2string2(in_file_name).find(".sam") != string::npos){
		if(char2string2(in_file_name).substr(char2string2(in_file_name).find(".sam"),4) == ".sam"){

			// count reads
			double total_read_count = 0;
			ifstream ifs_in_file_tmp(in_file_name);
			string line_tmp;
			while(getline(ifs_in_file_tmp, line_tmp)){
				if(line_tmp[0] != '@'){
					total_read_count++;
				}
			}

			// Get start time
			time_t start = time(0);

			string line = "";
			int line_count = 0;
			while(getline(ifs_in_file, line)){
				if(line[0] != '@'){

					/* get sam data */
					vector<string> record;
					algorithm::split(record,line,boost::is_any_of("\t"));
					flag = string2int(record[1]);
					rname = record[2];
			    	if(line_count == 0){
			    		rnamePre = rname;
			    	}
					pos = string2int(record[3]);
					mapq = string2int(record[4]);
					cigar = record[5];
					seq = record[9];
					qual = record[10];

					line_count++;
					if(line_count % 100000 == 0 || rname != rnamePre){
						time_t now = time(0);
						ofs_vcf_log << time() << "\t";
						char log[256];
						sprintf(log, "%'d",line_count);
						ofs_vcf_log << log << "\t";
						ofs_vcf_log << rname << ":" << pos << "\t";
						ofs_vcf_log << convSec(((total_read_count - line_count) / (line_count / difftime(now, start)))) << endl;
						printVcf();
					}
					rnamePre = rname;

					/* check error flags */
			    	if(checkErrFlags() == 1){
			    		// Get next read alignment data
			    		continue;
			    	}

					/* check bad cigar */
			    	if(checkBadCigar() == 1){
						continue;
			    	}

					/* check MAPQ */
					if(mapq < min_mapq){
						continue;
					}

					// get aux tags (x0, x1 and mdz)
					getAuxTagsForSAM(record);

					// check uniq alignment
					if(checkUniqMap() == 0){
						continue;
					}

					// delete both ends of seq
					delSeqEnds();

					// mark regions neighboring INDELs
					if(cigar.find('I') != string::npos || cigar.find('D') != string::npos){
						markNeiIndels();
					}

					// pileup sequences
					pileup();

					// clean variables for the next sam record
					cleanVariablesForSAM();

				}

			}
		}
	}

	// convert remained pileup to vcf and output vcf
	printRemainedVcf();

	seq_pile.clear();

	cout << "END: Heap::run " << in_file_name << " " << time() <<  endl;
	ofs_vcf_log << "END: Heap::run " << in_file_name << " " << time();
	ofs_vcf_log <<  endl;

	ifs_in_file.close();
	ofs_vcf_log.close();
}

int main(int argc, char *argv[]){
	setvbuf(stdout, (char *)NULL, _IONBF, 0); // disablement of output buffer to overwrite of progress
	setlocale(LC_NUMERIC,"ja_JP.utf8"); // setlocale to show number with comma

	string version = "Heap version 0.7.8";

	// test required tools
	// check bgzip
	int testCommandRet;
	string testCommand = "which bgzip";
	testCommandRet = std::system(string2char2(testCommand));
	if(testCommandRet != 0){
		cout << "bgzip is not installed or is not found in your path." << endl;
		exit(-1);
	}

	// check tabix
	testCommand = "which tabix";
	testCommandRet = std::system(string2char2(testCommand));
	if(testCommandRet != 0){
		cout << "tabix is not installed or is not found in your path." << endl;
		exit(-1);
	}

	// check bcftools
	testCommand = "which bcftools";
	testCommandRet = std::system(string2char2(testCommand));
	if(testCommandRet != 0){
		cout << "bcftools is not installed or is not found in your path." << endl;
		exit(-1);
	}

	// check bcftools version
	testCommand = "bcftools -v | grep bcftools | cut -d ' ' -f2 > bcftools_version.txt";
	testCommandRet = std::system(string2char2(testCommand));
	if(testCommandRet != 0){
		cout << "Command Error: " << testCommand << endl;
		exit(-1);
	}else{
		ifstream ifs("bcftools_version.txt");
		string version;
		getline(ifs, version);
		cout << "bcftools version " << version << endl;
		if(string2int(version) >= 1.1){
			cout << "bcftools version 1.1 or more is required" << endl;
			exit(-1);
		}
		ifs.close();
	}

	// get Heap command
	string heap_command = "";
	for(int i = 0; i < argc; i++){
		if(i == 0){
			heap_command += "Heap ";
		}else{
			char *p;
			p = argv[i];
			heap_command += char2string2(p) + " ";
		}
	}
	heap_command += "\n";

	// get start time
	string start_time_str = time_str();

	// prepare object for program options
	options_description opt("options");

	// definition of options
	opt.add_options()
		("version,v", "Show version")
		("help,h", "Show help")
		("ref,r", value<string>(), "Reference sequences used for the mapping in FASTA format")
		("in_files,i", value<vector<string> >(), "Aligned reads in BAM or SAM format which must be sorted")
		("out_file,o", value<string>(), "Prefix of output VCF file")
		("min_mapq,m", value<int>()->default_value(20), "Minimum MAPQ value")
		("min_base_qual,b", value<int>()->default_value(13), "Minimum phred scaled base quality score")
		("min_depth,d", value<unsigned int>()->default_value(3), "Minimum read depth")
		("del_end_length,e", value<int>()->default_value(2), "Deletion length at the both ends of reads (for RAD-Seq, 2 is recommended)")
		("ignore_indel_length,l", value<int>()->default_value(5), "Length of INDEL flanking regions to ignore")
		("thread_num,t", value<unsigned int>()->default_value(1), "Number of threads")
		("p_val,p", value<float>()->default_value(0.05), "P-value for Chi-squared test in genotyping")
	;
	// analyze options
	variables_map argmap;
	try{
		store(parse_command_line(argc, argv, opt), argmap);
	}
	catch(const std::exception& e){
		cout << e.what() << endl;
	}
	notify(argmap);

	// exit with version printing if -v was set
	if(argmap.count("version")) {
		cout << version << endl;
		return 1;
	}

	// exit with help printing if -h was set or required options was not set
	if(argmap.count("help")) {
		cout << opt << endl;
		return 1;
	}

	// exit with help printing if -h was set or required options was not set
	if(!argmap.count("in_files") || !argmap.count("ref") || !argmap.count("out_file")) {
		cerr << opt << endl;
		return 1;
	}

	// assign options to variables
	string ref_file = argmap["ref"].as<string>();
	vector<string> in_files;
	if(argmap.count("in_files")) {
		in_files = argmap["in_files"].as<vector<string> >();
	}
	string out_file = argmap["out_file"].as<string>();
	int min_mapq = argmap["min_mapq"].as<int>();
	int min_base_qual = argmap["min_base_qual"].as<int>();
	unsigned int min_depth = argmap["min_depth"].as<unsigned int>();
	int del_end_length = argmap["del_end_length"].as<int>();
	int ignore_indel_length = argmap["ignore_indel_length"].as<int>();
	unsigned int thread_num = argmap["thread_num"].as<unsigned int>();
	float p_val = argmap["p_val"].as<float>();
	int comp_p = static_cast<int>(round(p_val * 100));
	float x2_1 = 0;
	if(comp_p == 1){
		x2_1 = 6.634896601;
	}else if(comp_p == 5){
		x2_1 = 3.841458821;
	}else if(comp_p == 10){
		x2_1 = 2.705543454;
	}else{
		cout << endl << "Error: p_val is accepted only 0.01, 0.05 or 0.1." << endl;
		exit(1);
	}

	// print execute parameters
	cout << "path/to/ref.fasta: " << ref_file << endl;
	cout << "path/to/in_files.sam:" << endl;
	for(unsigned int i = 0; i < in_files.size(); i++){
		cout << in_files[i] << endl;
	}
	cout << "path/to/out_file.vcf: " << out_file << endl;
	cout << "Min MAPQ: " << min_mapq << endl;
	cout << "Min base quality: " << min_base_qual << endl;
	cout << "Min depth: " << min_depth << endl;
	cout << "length of read end deletion: " << del_end_length << endl;
	cout << "Number of threads: " << thread_num << endl;
	cout << "P-value for Chi-square test: " << p_val << "(x2=" << x2_1 << ")" << endl;

	// genotyping and SNP calling
	cout << "START: genotyping and SNP calling " << time() <<  endl;
	vector<string> vcf_file_name;
	unsigned int rest_files_num = in_files.size();
	for(unsigned int f = 0; f < in_files.size(); f++){
		// original
		if(rest_files_num >= thread_num){
			thread_group thr_grp;
			Heap *heap = new Heap[thread_num];
			for(unsigned int i = 0; i < thread_num; i++){
				vcf_file_name.push_back(removeFilePath(in_files[f]) + ".raw.vcf");
				heap[i].set(min_mapq, min_base_qual, del_end_length, ignore_indel_length, min_depth, string2char2(in_files[f]), string2char2(vcf_file_name[f]), x2_1, heap_command, string2char2(ref_file));
				thr_grp.create_thread(bind(&Heap::run, &heap[i]));
				f++;
			}
			thr_grp.join_all();
			delete [] heap;
			heap = NULL;
			rest_files_num = rest_files_num - thread_num;
			f--;
		}else{
			thread_group thr_grp;
			Heap *heap = new Heap[rest_files_num];
			for(unsigned int i = 0; i < rest_files_num; i++){
				vcf_file_name.push_back(removeFilePath(in_files[f]) + ".raw.vcf");
				heap[i].set(min_mapq, min_base_qual, del_end_length, ignore_indel_length, min_depth, string2char2(in_files[f]), string2char2(vcf_file_name[f]), x2_1, heap_command, string2char2(ref_file));
				thr_grp.create_thread(bind(&Heap::run, &heap[i]));
				f++;
			}
			thr_grp.join_all();
			delete [] heap;
			heap = NULL;
			f--;
		}

	}
	cout << "END: genotyping and SNP calling " << time() <<  endl;

	// bgzip raw VCFs each sample
	cout << "START: bgzip " << time() <<  endl;
	for(unsigned int f = 0; f < vcf_file_name.size(); f++){
		string command = "bgzip -f " + vcf_file_name[f];
		string command_echo = "echo " + command;
		std::system(string2char2(command_echo));
		std::system(string2char2(command));
		command = "tabix " + vcf_file_name[f] + ".gz";
		command_echo = "echo " + command;
		std::system(string2char2(command_echo));
		std::system(string2char2(command));
	}
	cout << "END: bgzip " << time() <<  endl;

	// merge raw VCFs and filter (drop off allele count < 1 and trim alternate alleles not seen in subset) merged VCF to output final VCF
	if(vcf_file_name.size()>1){
		cout << "START: merge VCFs " << time() <<  endl;
		string command = "bcftools merge -m all ";
		for(unsigned int f = 0; f < vcf_file_name.size(); f++){
			command += vcf_file_name[f] + ".gz ";
		}
		command += "| bgzip -c > " + out_file + ".raw.vcf.gz";
		std::system(string2char2(command));
		cout << "END: merge VCFs " << time() <<  endl;

		cout << "START: filter raw VCF " << time() <<  endl;
		command = "bcftools view -a -c 1 " + out_file + ".raw.vcf.gz | bgzip -f > " + out_file + ".vcf.gz";
		std::system(string2char2(command));
		cout << "END: filter raw VCF " << time() <<  endl;
	}else{
		cout << "START: filter raw VCF " << time() <<  endl;
		string command = "bcftools view -a -c 1 " + vcf_file_name[0] + ".gz | bgzip -f > " + out_file + ".vcf.gz";
		std::system(string2char2(command));
		cout << "END: filter raw VCF " << time() <<  endl;
	}
}
