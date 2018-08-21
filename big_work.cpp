#include<iostream>
#include<string>
using namespace std;

//int city_amounts; //ȫ�ֱ������ڴ�ų������� 
int attack_input[5]={20,50,50,50,50},elements_input[5]={10,20,50,50,30};// dragon ��ninja��iceman��lion��wolf
string red_sort[5]={"iceman","lion","wolf","ninja","dragon"};
int red_count;
string blue_sort[5]={"lion","dragon","ninja","iceman","wolf"};
int blue_count;

class CCreature;
//void CCreature::forward();
class CDragon;
class CCity;
class CBase;
void time_show();
void time_add();
void time_init();


class CBase
{
	
	int i;//�������˳������� 
	int elements_base;

	public:
	
	int loser;	
	int soldiers_num;//������ʿ������ 
	int soldiers_died;//����ʿ������ 	
		
		
	void award_soldiers();//����ʿ������ 
	
	
	friend class CCreature;
	friend class CCity;
	
	friend void soldiers_forward(CBase *red,CBase *blue);
	
	CCity *closest_city;//��ӽ����˻��صĳ��У��������Ƚ�������з�˾�������ʿ
	void set_closest_city(CCity *p)//��������˻�������ĳ��� 
	{closest_city=p; } 
	
	int enemy_amount;//�����е�������
	CBase *enemy_base;//ָ�����
	CCreature *enemy[2];//�������飬��������صĵ��˷���������� 
	
	//int city_amounts;//���е�������ʿ�����ڳ��г�ʼ��ţ���Ӵ�-1��ʼ��һ�����Ӵ�n��ʼ��һ
	
	string signal;//���ر�־������Ϊblue���Ϊred
	
	//CDragon a(1,20,30,this);
	CCreature *soldiers[100]={};//ʿ������ 
	CCreature *soldiers_died_arr[100]={};
	//CBase(int e,int c,string p):elements_base(e),city_amounts(c),signal(p)//��ʼ��������Ԫ�������б�ų�ʼֵ�����ر�־�� 
	CBase(int e,string p):elements_base(e),signal(p)//��ʼ��������Ԫ�������б�ų�ʼֵ�����ر�־�� 
	{ 
	  loser=0;
	  soldiers_num=0;
	  soldiers_died=0;
	  enemy_amount=0;
	  i=0;      //�������˳������� 
	  enemy_base=0;
	}
	
	void add_elements(int n){elements_base+=n;}
	
	void soldiers_born()
	{
	  if(signal=="red")
	  make_soldiers(red_sort[i]);
	  else if(signal=="blue")
	  make_soldiers(blue_sort[i]);
	}
	void make_soldiers(string s); 
	void add_soldiers(){soldiers_num+=1;	}
	void died_sodiers(){soldiers_died+=1;}

    void get_city_elements( CCreature *p[],int soldiers_num);//��ȡ���е�����Ԫ������Ϊ��һ������ 
    
	void base_report()
	{
		time_show();
		cout<<elements_base<<" elements in "<<signal<<" headquarter"<<endl;
	}
	void base_occupied()
	{
		loser=1;
		time_show();
		cout<<signal<<" headquartet was taken"<<endl;
		cout<<"-------game over-------"<<endl;
		exit(0);
	}
	
	void set_enemy(CBase *p)
	{
		enemy_base=p;
	}
//	int return_soldiers(){return soldiers_num;	} 
};


class CCity
{
	int elements_city; //������ӵ�е�����Ԫ���� 
	
	char flag;//flag='n'���� flag='r'���� flag='b'���� 
	int nblue;//������ʤ���� 
	int nred;//�����ʤ���� 
	
	public:
	int soldiers;//������ʿ�������� 
	int num;//���б��
	CCreature *blue;//ָ�򵽴�ó��е�����ʿ�� 
	CCreature *red; //ָ�򵽴�ó��еĺ��ʿ�� 
	
	CCity *last;//���ڳ��д���ָ����һ������ �����С�ģ�
	void set_last_city(CCity *p){last=p;	} //����ָ�� 
	CCity *next; //���ڳ��д���ָ����һ�����У���Ŵ�ģ�
	void set_next_city(CCity *p){next=p;	}  //����ָ��
	
	friend class CCreature;
	friend class CBase;
	CCity(int n,CCity *plast=0,CCity *pnext=0):num(n),last(plast),next(pnext)//���캯�� 
	{
	flag='n';
	nblue=0;
	nred=0;
	elements_city=0;
	soldiers=0;
	red=0;
	blue=0;
	} 
	
	void make_elements(){elements_city+=10;}//��������Ԫ 
	
	int get_elements()
	{int temp=elements_city;elements_city=0;return temp;}//��ȡ�ó��е�����Ԫ 
	
	void add_blue()//����ʤ��������һ��������ʤ���� 
	{
		if(nred==1)
		nred=0;
		nblue+=1;
		if(nblue==2)
		setflag('b');
	}
	
	void add_red()//���ʤ��������һ�κ����ʤ���� 
	{
		if(nblue==1)
		nblue=0;
		nred+=1;
		if(nred==2)
		setflag('r');
	}
	
	
	void setflag(char f)//���ó������� 
	{flag=f;
	 time_show();
	 if(f=='b')
	 cout<<"blue flag raised in city "<<num<<endl;
	 else if(f=='r')
	 cout<<"red flag raised in city "<<num<<endl;
	 else
	 cout<<"flag signal error!"<<endl;
	}
	
	void arrive_city(CCreature *p);//������� 
	void depart_city(CCreature *p);//�뿪���� 
	 
	char showflag(){return flag;}//չʾ�������� 
	//CCity& operator=(int n){num=n;	}
};




class CCreature
{
	protected:
    int num;//��� 

	
	
	
	CCity *city;//ָ��ʿ�����ڳ���
	//CCity *city_next; //ָ����һ�����ᵽ��ĳ��У�Ϊ0ʱ��������һ������з�˾� 

//	int city_num;//���б�ţ���ӳ�ʼֵΪ-1��������ʼֵΪn

	
	public:
	CBase *base;//ָ���ʿ���������� 
	friend class CBase;
	friend class CCity;
	
	string name;
	string belong;
	
	int force;//������
	int elements;//����ֵ
	int victory;//ʤ����־����ʼֵΪ0��ʤ������һ��ǰ������һ�����г�ʼ��Ϊ0  
	
	CCreature(int n,int e,int f,CBase* b):num(n),elements(e),force(f),base(b) 
	{ 
	   b->add_soldiers();//ʿ����������+1 
	  //if(b->signal=="red")
	 // city_num=-1;
	  //else if(b->signal=="blue")
	  //city_num=b->city_amounts; 
	  city=0;
	  //b->soldiers[b->soldiers_num-1]=0;
	  belong=b->signal;	
	} 
	
	void info()//�ԡ�blue lion 2 "����ʽ�����Ϣ 
	{
		cout<<belong<<" "<<name<<" "<<num<<" ";
	}

    void hurted(int power,CCreature *p)//ָ��P��������˺���ʩ���� 
	{	elements-=power;
		if(elements<=0)
		{
		 p->victory=1;
		 if(p->base->signal=="blue")
		 city->add_blue();
		 else if(p->base->signal=="red")
		 city->add_red();
		 died();
		}
	}
	
	virtual void attack(CCreature *p){};
	virtual void fightback(CCreature *p){}; 
	void died()
	{
		time_show();
		info();
		cout<<"was killed in city "<<city->num<<endl;
		city->depart_city(this);//������Ҫ�����뿪���ڳ��� 
		base->soldiers_died_arr[base->soldiers_died]=this;//����ʿ�����������ʿ������ 
		base->died_sodiers();
		base->soldiers[num-1]=0;//��ʿ��������ɾȥ 
		
	} 
	
	void earn_elements()//��ȡ��������Ԫ 
	{  
	   int temp=city->get_elements();
	   if(temp==0)
	   return;
	   base->add_elements(temp); 
	   time_show();
	   info();
	   cout<<"earned "<<temp<<" elements for his headquarter"<<endl;
	}
	
	virtual void forward()//ǰ��һ������ �������ں��++�����ӡ���
	{
		if(belong=="blue")
		{ 
		   if(city!=0)
		   {
		   	if(city->last==0)
		   {
		   	 city->depart_city(this);
		     occupy_base();
	       }
	        else
		   {
		   	 city->depart_city(this);
		     city->last->arrive_city(this);
	       }
		   }
		   else
		   base->enemy_base->closest_city->arrive_city(this);
		  
		}
		else if(belong=="red")
		{
		
			if(city!=0)//city=0�����ڻ��أ������ڴ����ڳ����� 
			{
			   if(city->next==0)
			  {
				city->depart_city(this);
				occupy_base();
			  }
			  else
			  {
		   	    city->depart_city(this);
		        city->next->arrive_city(this);
	          }
	        }
	        
	        else
	          { 
	            base->enemy_base->closest_city->arrive_city(this);
			  } 
		 } 
		// time_show();
	}
	 
	void occupy_base()//սʿ�ִ�о�˾�
	{
		int temp=base->enemy_base->enemy_amount++;//temp���ڱ�ע���ص��������±� 
		time_show();
		info();
		cout<<"reached "<<base->enemy_base->signal<<" headquarter with ";
		cout<<elements<<" elements and force "<<force<<endl; 
		base->enemy_base->enemy[temp]=this;
		base->soldiers[num-1]==0;//ʿ������о�˾����ӻʿ��������ɾ�� 
		if(base->enemy_base->enemy_amount==2)
		base->enemy_base->base_occupied();
	
	} 
	

};




void CCity::arrive_city(CCreature *p)
	{
		if(p->belong=="red")
		red=p;
		else if(p->belong=="blue")
        blue=p;
		else
		{cout<<"creature belong error!"<<endl;return;}
		
		soldiers++; //��ͬһ�������е�ʿ����+1 
		time_show();
		p->info();
		cout<<"marched to city "<<num<<" with "<<p->elements;
		cout<<" elements and force "<<p->force<<endl;
		p->city=this;
		p->victory=0;//����һ�����У�ʤ����־����
	}

void CCity::depart_city(CCreature *p)
{
	if(p->belong=="red")
	{
	   red=0;
	   soldiers--;
	   //if(num==(p->base->city_amounts-1))//����뿪���Ϊn-1�ĳ��У�����һ��������з����� 
	   //p->occupy_base();
	
	}
	else if(p->belong=="blue")
	{
	  blue=0;
	  soldiers--;
	 // if(num==0)//�����뿪���Ϊ0�ĳ��У�����һ��������з����� 
	//  p->occupy_base();
	  }
	else
	{cout<<"creature belong error!"<<endl;return;}
	
	//p->city=0;//�뿪���У�ָ����е�ָ������ 
	p->victory=0;//�뿪һ�����У�ʤ����־����
}




class CDragon:public CCreature
{
	
	public:
	CDragon(int n,int e,int f,CBase* b):CCreature(n,e,f,b)
	{
	  name="dragon";
	  time_show();
	  info();
	  cout<<"born"<<endl;	
	}

	virtual void attack(CCreature *p)//���� 
	{
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
		
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//��ȡ�ó�������Ԫ 
	    }
	    else
		p->fightback(this);//ʤ�����ȡ����Ԫ������Է�����
		 
		if(elements>0)//dragonս����δ������ 
		{
			time_show();
			info();
			cout<<"yelled in city"<<city->num<<endl;
		}
	 } 
	
	virtual void fightback(CCreature *p)//���� 
	{
		if(elements<=0)
		return;
		
		time_show();
		info();
		cout<<"fought back against ";
		p->info();
		cout<<"in city "<<city->num<<endl; 	
		
		p->hurted(force*0.5,this);
	}
};

class CNinja:public CCreature
{
	
	public:
	CNinja(int n,int e,int f,CBase* b):CCreature(n,e,f,b)
	{
	  name="ninja";
	  time_show();
	  info();
	  cout<<"born"<<endl;	
	}

	virtual void attack(CCreature *p)//���� 
	{
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
	
	
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//��ȡ�ó�������Ԫ 
	    }
		p->fightback(this);  
	 } 
	 
	 virtual void fightback(CCreature *P)//�����˲�������
	 {
	 	return;
	 }
};


class CIceman:public CCreature
{
	int steps;//��ʾǰ���Ĳ��� 
	public:
	
	CIceman(int n,int e,int f,CBase* b):CCreature(n,e,f,b)
	{
	  name="iceman";
	  steps=0;
	  time_show();
	  info();
	  cout<<"born"<<endl;	
	}

	virtual void attack(CCreature *p)//���� 
	{
		
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
		
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//��ȡ�ó�������Ԫ 
	    }
		p->fightback(this);
		if(elements<=0)//lionս����δ������ 
		died(); 
	 } 
	
	virtual void fightback(CCreature *p)//���� 
	{
		if(elements<=0)
		return;
		
		time_show();
		info();
		cout<<"fought back against ";
		p->info();
		cout<<"in city "<<city->num<<endl; 	
		
		p->hurted(force*0.5,this);
	}
	
	void step_add()
	{
		steps+=1;
	   if(steps==2)//ÿǰ���������ڵ�2����ɵ�ʱ������ֵ�����9��������������20��
	   //����������ֵ��9���С�ڵ���0��������ֵ����9,���Ǳ�Ϊ1����iceman�������߶��˶�����
	   {
	   	if(elements>9)
	   	 {
	   		elements-=9;
	   		force+=20;
		 }
		else
		elements=1; 
		steps=0; 
	   }
	}


virtual	void forward()//ǰ��һ������ �������ں��++�����ӡ���
	{
		if(belong=="blue")
		{ 
		   if(city!=0)
		   {
		   	if(city->last==0)
		   {
		   	 city->depart_city(this);
		     occupy_base();
	       }
	        else
		   {
		   	 city->depart_city(this);
		   	 step_add();
		     city->last->arrive_city(this);
	       }
		   }
		   else
		   {
		      base->enemy_base->closest_city->arrive_city(this);
		      step_add();
		  }
		  
		}
		else if(belong=="red")
		{
		
			if(city!=0)//city=0�����ڻ��أ������ڴ����ڳ����� 
			{
			   if(city->next==0)
			  {
				city->depart_city(this);
				occupy_base();
			  }
			  else
			  {
		   	    city->depart_city(this);
		   	    step_add();
		        city->next->arrive_city(this);
	          }
	        }
	        
	        else
	          { 
	            base->enemy_base->closest_city->arrive_city(this);
	            step_add();
			  } 
		 } 
	}

	
	
};



class CLion:public CCreature
{
	int elements_before;
	public:
	CLion(int n,int e,int f,CBase* b):CCreature(n,e,f,b)
	{
	  name="lion";
	  elements_before=0;
	  time_show();
	  info();
	  cout<<"born"<<endl;	
	}

    void hurted(int power,CCreature *p)//�ض���hurted������ָ��P��������˺���ʩ���� 
	{	elements_before=elements; 
	    elements-=power;
		if(elements<=0)
		{
			if(p->name=="wolf")//�����wolfɱ���������Լӱ�������Ѫ 
			{
				p->elements*=2;
				p->force*=2;
			}
		 p->elements+=elements_before;
		 p->victory=1;
		 if(p->base->signal=="blue")
		 city->add_blue();
		 else if(p->base->signal=="red")
		 city->add_red();
		 died();
		}
	}


	virtual void attack(CCreature *p)//���� 
	{   
	
	    time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
	     
	    elements_before=elements;
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//��ȡ�ó�������Ԫ 
	    }
		p->fightback(this);
		if(elements<=0)//lionս������ֵת�Ƶ��������� 
	    {
		  p->elements+=elements_before;
		  died();
     	}
	 } 
	
	virtual void fightback(CCreature *p)//���� 
	{
		if(elements<=0)
		return;
		
		time_show();
		info();
		cout<<"fought back against ";
		p->info();
		cout<<"in city "<<city->num<<endl; 
			
		p->hurted(force*0.5,this);
	}
};


class CWolf:public CCreature
{
	int killed_amount;
	public:
	CWolf(int n,int e,int f,CBase* b):CCreature(n,e,f,b)
	{
	  name="wolf";
	  killed_amount=0;
	  time_show();
	  info();
	  cout<<"born"<<endl;	
	}
	
	void double_ef(CCreature *p)//����Ԫ������ֵ���� 
	{
		if(killed_amount==2)
		{
		  if(p->name!="lion")//ɱ���ĵ��˷�lion 
		  {
		   elements*=2;
		   force*=2;
	      }
	    killed_amount=0;
		
	    }
	}

	virtual void attack(CCreature *p)//���� 
	{
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
		
		p->hurted(force,this);
		if(victory==1)
		{
			killed_amount+=1;
			double_ef(p);
		//	earn_elements();//��ȡ�ó�������Ԫ 
	    }
	    else 
		p->fightback(this);
		if(elements<=0)//���������� 
		died(); 
	 } 
	
	virtual void fightback(CCreature *p)//���� 
	{
		if(elements<=0)
		return;
		
		time_show();
		info();
		cout<<"fought back against ";
		p->info();
		cout<<"in city "<<city->num<<endl; 
		
		p->hurted(force*0.5,this);
			
	}
};


void CBase::make_soldiers(string s)
{
	if(s=="dragon")
	{
	  if(elements_base>=elements_input[0])//���ص�����Ԫ������ʿ�� 
	  { soldiers[soldiers_num-1]=new CDragon(soldiers_num+1,elements_input[0],attack_input[0],this);//��ţ�����Ԫ������������������ 
	    
	    elements_base-=elements_input[0];
	
	  }
	  else//���ص�����Ԫ��������ʿ���� 
	  {cout<<"ԭ�ϲ���"<<endl;
	   return; 
	  }
    }
	else if(s=="ninja")
	{
	  if(elements_base>=elements_input[1])//���ص�����Ԫ������ʿ�� 
	  { soldiers[soldiers_num-1]=new CNinja(soldiers_num+1,elements_input[1],attack_input[1],this);//��ţ�����Ԫ������������������ 
	    elements_base-=elements_input[1]; 
	  }
	  else//���ص�����Ԫ��������ʿ���� 
	  {cout<<"ԭ�ϲ���"<<endl;
	   return; 
	  }
    }
	else if(s=="iceman")
	{
	  if(elements_base>=elements_input[2])//���ص�����Ԫ������ʿ�� 
	  { soldiers[soldiers_num-1]=new CIceman(soldiers_num+1,elements_input[2],attack_input[2],this);//��ţ�����Ԫ������������������
	 // cout<<soldiers_num<<endl; 
	 // cout<<soldiers[0]<<endl;
	    elements_base-=elements_input[2]; 
	  }
	  else//���ص�����Ԫ��������ʿ���� 
	  {cout<<"ԭ�ϲ���"<<endl;
	   return; 
	  }
    }

	else if(s=="lion")
	{
	  if(elements_base>=elements_input[3])//���ص�����Ԫ������ʿ�� 
	  { soldiers[soldiers_num-1]=new CLion(soldiers_num+1,elements_input[3],attack_input[3],this);//��ţ�����Ԫ������������������ 
	    elements_base-=elements_input[3]; 
	  }
	  else//���ص�����Ԫ��������ʿ���� 
	  {cout<<"ԭ�ϲ���"<<endl;
	   return; 
	  }
    }
    
	else if(s=="wolf")
	{
	  if(elements_base>=elements_input[4])//���ص�����Ԫ������ʿ�� 
	  { soldiers[soldiers_num-1]=new CWolf(soldiers_num+1,elements_input[4],attack_input[4],this);//��ţ�����Ԫ������������������ 
	    elements_base-=elements_input[4]; 
	  }
	  else//���ص�����Ԫ��������ʿ���� 
	  {cout<<"ԭ�ϲ���"<<endl;
	   return; 
	  }
    } 
  i++;
  if(i>=5)
  i=0;
}


void CBase::award_soldiers()
{
	CCity *temp=closest_city;

	while(elements_base>=8)
	{

		if(signal=="red")
		{
			if(temp->red!=0)
           {

			if(temp->red->victory==1)
			{
			  temp->red->elements+=8;
			  elements_base-=8;
	     	}
           }
	     	 temp=temp->last;
		}
		else if(signal=="blue")
		{
		  if(temp->blue!=0)
		  {

			if(temp->blue->victory==1)
			{
		    	temp->blue->elements+=8;
			    elements_base-=8;
			}

	      }
			temp=temp->next;
		}

		if(temp==0)
		break;
	}
} 

void CBase::get_city_elements(CCreature *p[],int soldiers_num)
{

	CCreature *temp;
	int i=0;
	while(i<soldiers_num)
	{   
		temp=p[i];
		if(temp!=0) 
		{
		 if(temp->city->soldiers==1)
		 temp->earn_elements();
	    }
		i++;

	 } 
}


//ȫ�ֱ��� 
//CCreature *blue[100];//����ʿ������ 
//CCreature *red[100];//���ʿ������

//int red_num, blue_num; //������ʿ������ 


int red_attack[5];// iceman��lion��wolf��ninja��dragon
int blue_attack[5];//lion��dragon��ninja��iceman��wolf 
int red_elements[5];
int blue_elements[5];
int time_minu,time_hour,time_total;




void award_soldiers(CBase* p);
void list_citys(CCity *citys[],int n_input);


void soldiers_born(CBase *red,CBase *blue);
void soldiers_forward(CBase *red,CBase *blue);
void city_make_elements(CCity *city);
void soldiers_get();
void soldiers_fight(CCity *city);
void base_report();


int main()
{  


    int n_circle;//һ�����뼸������ 
    int i,j,k;//���ڼ���ѭ�� 
    int m_input,n_input,t_input;//������������ 
    //ÿ��˾�һ��ʼ����M������Ԫ( 1 <= M <= 1000)
    //����˾�֮��һ����N������( 1 <= N <= 20 )
    //Ҫ�������0ʱ0�ֿ�ʼ����ʱ��TΪֹ(����T) �������¼���T�Է���Ϊ��λ��0 <= T <= 1000


	cin>>n_circle;        //�û�����һ����n_circle������ 
    for(i=0;i<n_circle;i++)//�û������������ 
    {
    	cin>>m_input>>n_input>>t_input;
    //	city_amount=n_input;
		CBase blue(m_input,"blue"),red(m_input,"red");//�������������������,���ӳ��б�Ŵ�n��ʼ����ӳ��б�Ŵ�-1��ʼ 
		
		blue.set_enemy(&red);//���ú�ӵз� 
		red.set_enemy(&blue);//�������ӵз� 
		CCity *citys[n_input];
		for(j=0;j<n_input;j++)
		citys[j]=new CCity(j);//������������
		
		list_citys(citys,n_input);//���������д������� 
		
		red.set_closest_city(citys[n_input-1]);//������з���������ĳ��� 
		blue.set_closest_city(citys[0]);
		 
		for(j=0;j<5;j++)
		cin>>elements_input[j];
		for(j=0;j<5;j++)
		cin>>attack_input[j];
	}




//	cin>>n_circle;        //�û�����һ����n_circle������ 
 //   for(i=0;i<n_circle;i++)//�û������������ 
  //  {
    //	cin>>m_input>>n_input>>t_input;
   // m_input=99;
   // n_input=2;
   // t_input=1000;
		CBase blue(m_input,"blue"),red(m_input,"red");//�������������������,���ӳ��б�Ŵ�n��ʼ����ӳ��б�Ŵ�-1��ʼ 
		
		blue.set_enemy(&red);//���ú�ӵз� 
		red.set_enemy(&blue);//�������ӵз� 
		CCity *citys[n_input];
		for(j=0;j<n_input;j++)
		citys[j]=new CCity(j+1);//������������
		
		list_citys(citys,n_input);//���������д������� 
		
		red.set_closest_city(citys[n_input-1]);//������з���������ĳ��� 
		blue.set_closest_city(citys[0]);
		 
	//	for(j=0;j<5;j++)
		//cin>>elements_input[j];
	//	for(j=0;j<5;j++)
	//	cin>>attack_input[j];
//	}






	
	red_count=0;
	blue_count=0;
	
   while(time_total<t_input)
  {
  	
	switch(time_minu)
    {
	case 0:
	    soldiers_born(&red,&blue); 
	    break;
	case 10:
	    soldiers_forward(&red,&blue);
	    if(red.loser==1||blue.loser==1)
	    {return 0;}
		break;
	case 20:
		city_make_elements(citys[0]);
		break;
	case 30:
		blue.get_city_elements(blue.soldiers,blue.soldiers_num);
		red.get_city_elements(red.soldiers,red.soldiers_num);
	    break;
	case 40:
		soldiers_fight(citys[0]);
		
		red.award_soldiers();

		blue.award_soldiers();

		blue.get_city_elements(blue.soldiers,blue.soldiers_num);

		red.get_city_elements(red.soldiers,red.soldiers_num);
	    break;
	case 50:
		red.base_report();
		blue.base_report();
	    break;
    }
    time_add();
    cout<<endl;

    //cout<<endl;
    //cout<<red.soldiers[0]<<endl;
   // cout<<red.soldiers[10]<<endl;
    //cout<<red.soldiers[0]->belong<<endl; 
	//red.soldiers[0]->info();
   // cout<<endl;
  } 



	return 0;
}




void soldiers_born(CBase *red,CBase *blue)
{
	red->make_soldiers(red_sort[red_count++]);
	if(red_count==5)
	red_count=0;
	blue->make_soldiers(blue_sort[blue_count++]);
	if(red_count==5)
	red_count=0;
}

void soldiers_forward(CBase *red,CBase *blue)
{
	int i,j;
	for(i=0;i<red->soldiers_num;i++)
	{
	    if(red->soldiers[i]!=0)
	    {
	    	//cout<<red->soldiers_num;
	    	//cout<<red->soldiers[0]->belong;
	    	//red->soldiers[0]->info();
	    	red->soldiers[i]->forward();
		}
		
	}
	for(j=0;j<blue->soldiers_num;j++)
	{
		//time_show();
		if(blue->soldiers[j]!=0)
		blue->soldiers[j]->forward();
	}
}

void city_make_elements(CCity *city)
{
	CCity* temp=city;
	while(temp)
	{
		temp->make_elements();
		temp=temp->next; 
	}
	
}


void soldiers_fight(CCity *city)
{
	CCity *temp=city;
	while(temp)
	{
		if(temp->soldiers==2)
		{
			if(temp->showflag()=='r')
			temp->red->attack(temp->blue);
			else if(temp->showflag()=='b')
			temp->blue->attack(temp->red);
			else if(temp->showflag()=='n')//���� 
			{
				if(temp->num%2==1)
				temp->red->attack(temp->blue);
				else if(temp->num%2==0)
				temp->blue->attack(temp->red);	
			}
		}
	temp=temp->next;

	}
}


void list_citys(CCity *citys[],int n_input)
{
	int i;
	for(i=1;i<n_input-1;i++)//���������д������� 
		{
			citys[i]->next=citys[i+1] ;
			citys[i]->last=citys[i-1];
		 } 
		 citys[0]->last=0;
		 citys[0]->next=citys[1];
		 citys[n_input-1]->next=0;
		 citys[n_input-1]->last=citys[n_input-2];
}


void time_show()
{
	if(time_hour<10)
	{
		if(time_minu==0)
		cout<<"00"<<time_hour<<":00 ";
		else
		cout<<"00"<<time_hour<<":"<<time_minu<<" ";  
	}
	else if(time_hour<100)
	{
		if(time_minu==0)
		cout<<"0"<<time_hour<<":00 ";
		else
		cout<<"0"<<time_hour<<":"<<time_minu<<" ";
	}
	else
	{
		if(time_minu==0)
		cout<<time_hour<<":00 ";
		else
		cout<<time_hour<<":"<<time_minu<<" ";
	}	
}



void time_add()
{
	time_minu+=10;
	if(time_minu==60)
	{
		time_minu=0;
		time_hour+=1;
	}
	time_total=time_hour*60+time_minu;
}

void time_init()
{
	time_minu=0;
	time_hour=0;
	time_total=0;
}
