#include<iostream>
#include<string>
using namespace std;

//int city_amounts; //全局变量用于存放城市数量 
int attack_input[5]={20,50,50,50,50},elements_input[5]={10,20,50,50,30};// dragon 、ninja、iceman、lion、wolf
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
	
	int i;//用于造兵顺序计数用 
	int elements_base;

	public:
	
	int loser;	
	int soldiers_num;//产生的士兵数量 
	int soldiers_died;//死亡士兵数量 	
		
		
	void award_soldiers();//奖励士兵函数 
	
	
	friend class CCreature;
	friend class CCity;
	
	friend void soldiers_forward(CBase *red,CBase *blue);
	
	CCity *closest_city;//最接近敌人基地的城市，用于优先奖励距离敌方司令部近的武士
	void set_closest_city(CCity *p)//设置离敌人基地最近的城市 
	{closest_city=p; } 
	
	int enemy_amount;//基地中敌人数量
	CBase *enemy_base;//指向敌人
	CCreature *enemy[2];//敌人数组，将进入基地的敌人放入该数组中 
	
	//int city_amounts;//城市的数量，士兵所在城市初始编号，红队从-1开始加一，蓝队从n开始减一
	
	string signal;//基地标志，蓝队为blue红队为red
	
	//CDragon a(1,20,30,this);
	CCreature *soldiers[100]={};//士兵数组 
	CCreature *soldiers_died_arr[100]={};
	//CBase(int e,int c,string p):elements_base(e),city_amounts(c),signal(p)//初始化（生命元数，城市编号初始值，基地标志） 
	CBase(int e,string p):elements_base(e),signal(p)//初始化（生命元数，城市编号初始值，基地标志） 
	{ 
	  loser=0;
	  soldiers_num=0;
	  soldiers_died=0;
	  enemy_amount=0;
	  i=0;      //用于造兵顺序计数用 
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

    void get_city_elements( CCreature *p[],int soldiers_num);//获取城市的生命元，参数为第一个城市 
    
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
	int elements_city; //城市所拥有的生命元数量 
	
	char flag;//flag='n'无旗 flag='r'红旗 flag='b'蓝旗 
	int nblue;//蓝队连胜次数 
	int nred;//红队连胜次数 
	
	public:
	int soldiers;//城市中士兵的数量 
	int num;//城市编号
	CCreature *blue;//指向到达该城市的蓝队士兵 
	CCreature *red; //指向到达该城市的红队士兵 
	
	CCity *last;//用于城市串，指向上一个城市 （编号小的）
	void set_last_city(CCity *p){last=p;	} //设置指针 
	CCity *next; //由于城市串，指向下一个城市（编号大的）
	void set_next_city(CCity *p){next=p;	}  //设置指针
	
	friend class CCreature;
	friend class CBase;
	CCity(int n,CCity *plast=0,CCity *pnext=0):num(n),last(plast),next(pnext)//构造函数 
	{
	flag='n';
	nblue=0;
	nred=0;
	elements_city=0;
	soldiers=0;
	red=0;
	blue=0;
	} 
	
	void make_elements(){elements_city+=10;}//产生生命元 
	
	int get_elements()
	{int temp=elements_city;elements_city=0;return temp;}//获取该城市的生命元 
	
	void add_blue()//蓝队胜利，增加一次蓝队连胜次数 
	{
		if(nred==1)
		nred=0;
		nblue+=1;
		if(nblue==2)
		setflag('b');
	}
	
	void add_red()//红队胜利，增加一次红队连胜次数 
	{
		if(nblue==1)
		nblue=0;
		nred+=1;
		if(nred==2)
		setflag('r');
	}
	
	
	void setflag(char f)//设置城市旗帜 
	{flag=f;
	 time_show();
	 if(f=='b')
	 cout<<"blue flag raised in city "<<num<<endl;
	 else if(f=='r')
	 cout<<"red flag raised in city "<<num<<endl;
	 else
	 cout<<"flag signal error!"<<endl;
	}
	
	void arrive_city(CCreature *p);//到达城市 
	void depart_city(CCreature *p);//离开城市 
	 
	char showflag(){return flag;}//展示城市旗帜 
	//CCity& operator=(int n){num=n;	}
};




class CCreature
{
	protected:
    int num;//编号 

	
	
	
	CCity *city;//指向士兵所在城市
	//CCity *city_next; //指向下一步将会到达的城市，为0时，代表下一步到达敌方司令部 

//	int city_num;//城市编号，红队初始值为-1，蓝方初始值为n

	
	public:
	CBase *base;//指向该士兵所属基地 
	friend class CBase;
	friend class CCity;
	
	string name;
	string belong;
	
	int force;//攻击力
	int elements;//生命值
	int victory;//胜利标志，初始值为0，胜利后置一，前进到另一个城市初始化为0  
	
	CCreature(int n,int e,int f,CBase* b):num(n),elements(e),force(f),base(b) 
	{ 
	   b->add_soldiers();//士兵生成数量+1 
	  //if(b->signal=="red")
	 // city_num=-1;
	  //else if(b->signal=="blue")
	  //city_num=b->city_amounts; 
	  city=0;
	  //b->soldiers[b->soldiers_num-1]=0;
	  belong=b->signal;	
	} 
	
	void info()//以“blue lion 2 "的形式输出信息 
	{
		cout<<belong<<" "<<name<<" "<<num<<" ";
	}

    void hurted(int power,CCreature *p)//指针P代表造成伤害的施暴者 
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
		city->depart_city(this);//死亡后要让他离开所在城市 
		base->soldiers_died_arr[base->soldiers_died]=this;//将该士兵添加至死亡士兵数组 
		base->died_sodiers();
		base->soldiers[num-1]=0;//从士兵数组中删去 
		
	} 
	
	void earn_elements()//获取城市生命元 
	{  
	   int temp=city->get_elements();
	   if(temp==0)
	   return;
	   base->add_elements(temp); 
	   time_show();
	   info();
	   cout<<"earned "<<temp<<" elements for his headquarter"<<endl;
	}
	
	virtual void forward()//前进一个城市 ，适用于红队++，蓝队——
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
		
			if(city!=0)//city=0代表在基地，不等于代表在城市中 
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
	 
	void occupy_base()//战士抵达敌军司令部
	{
		int temp=base->enemy_base->enemy_amount++;//temp用于标注基地敌人数组下标 
		time_show();
		info();
		cout<<"reached "<<base->enemy_base->signal<<" headquarter with ";
		cout<<elements<<" elements and force "<<force<<endl; 
		base->enemy_base->enemy[temp]=this;
		base->soldiers[num-1]==0;//士兵到达敌军司令部，从活动士兵数组中删除 
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
		
		soldiers++; //在同一个城市中的士兵数+1 
		time_show();
		p->info();
		cout<<"marched to city "<<num<<" with "<<p->elements;
		cout<<" elements and force "<<p->force<<endl;
		p->city=this;
		p->victory=0;//到达一个城市，胜利标志置零
	}

void CCity::depart_city(CCreature *p)
{
	if(p->belong=="red")
	{
	   red=0;
	   soldiers--;
	   //if(num==(p->base->city_amounts-1))//红队离开编号为n-1的城市，即下一步将进入敌方基地 
	   //p->occupy_base();
	
	}
	else if(p->belong=="blue")
	{
	  blue=0;
	  soldiers--;
	 // if(num==0)//蓝队离开编号为0的城市，即下一步将进入敌方基地 
	//  p->occupy_base();
	  }
	else
	{cout<<"creature belong error!"<<endl;return;}
	
	//p->city=0;//离开城市，指向城市的指针置零 
	p->victory=0;//离开一个城市，胜利标志置零
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

	virtual void attack(CCreature *p)//攻击 
	{
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
		
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//获取该城市生命元 
	    }
	    else
		p->fightback(this);//胜利则获取生命元，否则对方反击
		 
		if(elements>0)//dragon战斗后未死欢呼 
		{
			time_show();
			info();
			cout<<"yelled in city"<<city->num<<endl;
		}
	 } 
	
	virtual void fightback(CCreature *p)//反击 
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

	virtual void attack(CCreature *p)//攻击 
	{
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
	
	
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//获取该城市生命元 
	    }
		p->fightback(this);  
	 } 
	 
	 virtual void fightback(CCreature *P)//挨打了不反击；
	 {
	 	return;
	 }
};


class CIceman:public CCreature
{
	int steps;//表示前进的步数 
	public:
	
	CIceman(int n,int e,int f,CBase* b):CCreature(n,e,f,b)
	{
	  name="iceman";
	  steps=0;
	  time_show();
	  info();
	  cout<<"born"<<endl;	
	}

	virtual void attack(CCreature *p)//攻击 
	{
		
		time_show();
		info();
		cout<<"attacked ";
		p->info();
		cout<<"in city "<<city->num<<" with "<<elements<<" elements and force "<<force<<endl;
		
		p->hurted(force,this);
		if(victory==1)
		{
		//	earn_elements();//获取该城市生命元 
	    }
		p->fightback(this);
		if(elements<=0)//lion战斗后未死欢呼 
		died(); 
	 } 
	
	virtual void fightback(CCreature *p)//反击 
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
	   if(steps==2)//每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。
	   //但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。
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


virtual	void forward()//前进一个城市 ，适用于红队++，蓝队——
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
		
			if(city!=0)//city=0代表在基地，不等于代表在城市中 
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

    void hurted(int power,CCreature *p)//重定义hurted函数，指针P代表造成伤害的施暴者 
	{	elements_before=elements; 
	    elements-=power;
		if(elements<=0)
		{
			if(p->name=="wolf")//如果被wolf杀死，先属性加倍，再吸血 
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


	virtual void attack(CCreature *p)//攻击 
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
		//	earn_elements();//获取该城市生命元 
	    }
		p->fightback(this);
		if(elements<=0)//lion战死生命值转移到对手身上 
	    {
		  p->elements+=elements_before;
		  died();
     	}
	 } 
	
	virtual void fightback(CCreature *p)//反击 
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
	
	void double_ef(CCreature *p)//生命元和武力值翻倍 
	{
		if(killed_amount==2)
		{
		  if(p->name!="lion")//杀死的敌人非lion 
		  {
		   elements*=2;
		   force*=2;
	      }
	    killed_amount=0;
		
	    }
	}

	virtual void attack(CCreature *p)//攻击 
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
		//	earn_elements();//获取该城市生命元 
	    }
	    else 
		p->fightback(this);
		if(elements<=0)//被反击致死 
		died(); 
	 } 
	
	virtual void fightback(CCreature *p)//反击 
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
	  if(elements_base>=elements_input[0])//基地的生命元够创造士兵 
	  { soldiers[soldiers_num-1]=new CDragon(soldiers_num+1,elements_input[0],attack_input[0],this);//编号，生命元，攻击力，所属基地 
	    
	    elements_base-=elements_input[0];
	
	  }
	  else//基地的生命元不够创造士兵； 
	  {cout<<"原料不足"<<endl;
	   return; 
	  }
    }
	else if(s=="ninja")
	{
	  if(elements_base>=elements_input[1])//基地的生命元够创造士兵 
	  { soldiers[soldiers_num-1]=new CNinja(soldiers_num+1,elements_input[1],attack_input[1],this);//编号，生命元，攻击力，所属基地 
	    elements_base-=elements_input[1]; 
	  }
	  else//基地的生命元不够创造士兵； 
	  {cout<<"原料不足"<<endl;
	   return; 
	  }
    }
	else if(s=="iceman")
	{
	  if(elements_base>=elements_input[2])//基地的生命元够创造士兵 
	  { soldiers[soldiers_num-1]=new CIceman(soldiers_num+1,elements_input[2],attack_input[2],this);//编号，生命元，攻击力，所属基地
	 // cout<<soldiers_num<<endl; 
	 // cout<<soldiers[0]<<endl;
	    elements_base-=elements_input[2]; 
	  }
	  else//基地的生命元不够创造士兵； 
	  {cout<<"原料不足"<<endl;
	   return; 
	  }
    }

	else if(s=="lion")
	{
	  if(elements_base>=elements_input[3])//基地的生命元够创造士兵 
	  { soldiers[soldiers_num-1]=new CLion(soldiers_num+1,elements_input[3],attack_input[3],this);//编号，生命元，攻击力，所属基地 
	    elements_base-=elements_input[3]; 
	  }
	  else//基地的生命元不够创造士兵； 
	  {cout<<"原料不足"<<endl;
	   return; 
	  }
    }
    
	else if(s=="wolf")
	{
	  if(elements_base>=elements_input[4])//基地的生命元够创造士兵 
	  { soldiers[soldiers_num-1]=new CWolf(soldiers_num+1,elements_input[4],attack_input[4],this);//编号，生命元，攻击力，所属基地 
	    elements_base-=elements_input[4]; 
	  }
	  else//基地的生命元不够创造士兵； 
	  {cout<<"原料不足"<<endl;
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


//全局变量 
//CCreature *blue[100];//蓝队士兵数组 
//CCreature *red[100];//红队士兵数组

//int red_num, blue_num; //红蓝队士兵数量 


int red_attack[5];// iceman、lion、wolf、ninja、dragon
int blue_attack[5];//lion、dragon、ninja、iceman、wolf 
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


    int n_circle;//一共输入几组数据 
    int i,j,k;//由于计数循环 
    int m_input,n_input,t_input;//用于输入数据 
    //每个司令部一开始都有M个生命元( 1 <= M <= 1000)
    //两个司令部之间一共有N个城市( 1 <= N <= 20 )
    //要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 1000


	cin>>n_circle;        //用户输入一共有n_circle组数据 
    for(i=0;i<n_circle;i++)//用户输入相关数据 
    {
    	cin>>m_input>>n_input>>t_input;
    //	city_amount=n_input;
		CBase blue(m_input,"blue"),red(m_input,"red");//创建基地类的两个对象,蓝队城市编号从n开始，红队城市编号从-1开始 
		
		blue.set_enemy(&red);//设置红队敌方 
		red.set_enemy(&blue);//设置蓝队敌方 
		CCity *citys[n_input];
		for(j=0;j<n_input;j++)
		citys[j]=new CCity(j);//创建城市数组
		
		list_citys(citys,n_input);//将各个城市串联起来 
		
		red.set_closest_city(citys[n_input-1]);//设置离敌方基地最近的城市 
		blue.set_closest_city(citys[0]);
		 
		for(j=0;j<5;j++)
		cin>>elements_input[j];
		for(j=0;j<5;j++)
		cin>>attack_input[j];
	}




//	cin>>n_circle;        //用户输入一共有n_circle组数据 
 //   for(i=0;i<n_circle;i++)//用户输入相关数据 
  //  {
    //	cin>>m_input>>n_input>>t_input;
   // m_input=99;
   // n_input=2;
   // t_input=1000;
		CBase blue(m_input,"blue"),red(m_input,"red");//创建基地类的两个对象,蓝队城市编号从n开始，红队城市编号从-1开始 
		
		blue.set_enemy(&red);//设置红队敌方 
		red.set_enemy(&blue);//设置蓝队敌方 
		CCity *citys[n_input];
		for(j=0;j<n_input;j++)
		citys[j]=new CCity(j+1);//创建城市数组
		
		list_citys(citys,n_input);//将各个城市串联起来 
		
		red.set_closest_city(citys[n_input-1]);//设置离敌方基地最近的城市 
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
			else if(temp->showflag()=='n')//无旗 
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
	for(i=1;i<n_input-1;i++)//将各个城市串联起来 
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
