#include"Transfers.h"

namespace Transfer{

	std::string i2s(int i){
		std::string s = "";
		if(i<0){
			s.append("-");
			i=-i;
		}
		if(i>9){
			s.append(i2s(i/10));
		}
		s.push_back('0'+i%10);
		return s;
	}
	std::string d2s(double val, int demi){
		std::string s = "";

		if(val<0.0f){
			s.append("-");
			val=-val;
		}
		int integer=(int)val;
		double demical=val-(double)integer;
		if(demi<1)demi=1;
		int t_demi=0;

		for(int looper=0; looper<demi; looper++){
			demical*=10;
		}

		t_demi=(int)(demical+0.5);

		s.append(i2s(integer));
		s.append(".");
		s.append(i2s(t_demi));

		return s;
	}
	int s2i(std::string s){
		if(s.length()==0)return 0;

		int r=0;
		bool b_minus = false;
		std::string::const_iterator it=s.begin();
		if(*it == '-'){
			b_minus = true;
			++it;
		}
		while(it!=s.end()){
			int dig=(*it)-'0';
			if(dig<0 || dig>9)return 0;
			r=r*10+dig;
			++it;
		}

		if(b_minus)r=-r;

		return r;
	}
	double s2d(std::string s){
		if(s.length()==0)return 0.0;

		double r=0.0;
		bool b_minus = false;
		std::string integer, demical;
		double d_int, d_demi;
		if(s.at(0)=='-')
			b_minus=true;

		int pt_pos = 0;
		pt_pos = s.find_first_of('.');

		if(pt_pos == -1){
			if(b_minus)
				integer = s.substr(1);
			else
				integer = s;
			demical = "";
		}else{
			if(b_minus)
				integer = s.substr(1,pt_pos-1);//-12.34 pt_pos=3    12.34 pt_pos=2
			else
				integer = s.substr(0,pt_pos);
			demical = s.substr(pt_pos+1);
		}

		d_int = (double)s2i(integer);
		d_demi = (double)s2i(demical);
		if(demical.length()>0) 
			for(unsigned int looper=0; looper<demical.length(); looper++){
				d_demi/=(double)10.0;
			}

		if(d_int<0.0)return 0.0;
		r=d_int+d_demi;
		if(b_minus)r=-r;

		return r;
	}

}