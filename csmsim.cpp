#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include <chrono>
#include <thread>
#define CPUBUFFER 1
#define DISK1BUFFER 1
#define DISK2BUFFER 1
using namespace std;
//can add disk enum
typedef int diskno;
const diskno emptyqueue=-1;
class Process
{
    int process_id;
    string process_name;
    queue<diskno> memqueue;
    public:
    /*Process()
    {
        process_name= new string;
    }*/
    void enqueue(diskno x)
    {
        memqueue.push(x);
    }
    diskno dequeue()
    {
        if(!memqueue.empty())
        {
            diskno x=memqueue.front();
            memqueue.pop();
            return x;
        }
        else
            return emptyqueue;
    }
    diskno getQueue()
    {
        if(!memqueue.empty())
            return memqueue.front();
        else
            return emptyqueue;
    }
    int getProcessID()
    {
        return process_id;
    }
    string getProcessName()
    {
        return process_name;
    }
    void setProcessID(int x)
    {
        process_id=x;
    }
    void setProcessName(string x)
    {
        process_name.clear();
        process_name=x;
    }
    void display()
    {
        cout<<process_id<<'\t'<<process_name;
    }
    void clear()
    {
        while(!memqueue.empty())
        {
            memqueue.pop();
        }
        process_name.clear();
    }
};

void printQueue(queue<Process> q)
{
	//printing content of queue
    //Process
	while (!q.empty()){
		//cout<<" "<<q.front();
        cout<<q.front().getProcessID()<<"\t\t"<<q.front().getProcessName()<<endl;
		q.pop();
	}
	cout<<endl;
}

int main()
{
    string pname;
    Process temp;
    int n,x,ch,time=0;
    queue<Process> cpu_queue,disk1_queue,disk2_queue;
    cout<<"\nEnter Number Of Processes:";
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cout<<"\nEnter Process "<<i<<"\'s Details:-\n";
        cout<<"Name:";
        pname.clear();
        cin>>pname;
        temp.setProcessName(pname);
        temp.setProcessID(i);
        cout<<"Enter Disk Access Queue (1 for Disk1,2 for Disk2 .Terminate with -1)\n";
        do{
            cin>>x;
            if(x==1||x==2)
            {
                temp.enqueue(x);
            }
            else if(x==-1)
            {
                break;
            }
            else
            {
                cout<<"Invalid Disk Number";
            }
        }while(x!=-1);
        cout<<"Enter The Initial State Of The Process (0:CPU,1:Disk1,2:Disk2):";
        cin>>ch;
        switch(ch)
        {
            case 0:cpu_queue.push(temp);break;
            case 1:disk1_queue.push(temp);break;
            case 2:disk2_queue.push(temp);break;
            default:cout<<"Invalid Choice.Defaulting To CPU";cpu_queue.push(temp);
        }
        temp.clear();      
    }
    int fl;
    while(!(cpu_queue.empty()&&disk1_queue.empty()&&disk2_queue.empty()))
    {
        fl=0;
        cout<<"\n**********************************************\n";
        cout<<"System State At "<<time<<" Seconds\n";
        if(!cpu_queue.empty()){
           cout<<"CPU Queue\n"<<"Process ID\tProcess Name\n"<<"----------------------------------\n";
           printQueue(cpu_queue);
        }
        else
            cout<<"CPU:Queue Empty\n";
        if(!disk1_queue.empty()){
            cout<<"Disk 1 Queue\n"<<"Process ID\tProcess Name\n"<<"----------------------------------\n";
            printQueue(disk1_queue);
        }
        else
            cout<<"Disk 1:Queue Empty\n";

        if(!disk2_queue.empty()){
            cout<<"Disk 2 Queue\n"<<"Process ID\tProcess Name\n"<<"----------------------------------\n";
            printQueue(disk2_queue);
        }
        else
            cout<<"Disk 2:Queue Empty\n";
        time++;
        Process temp,temp1;
        if(((time%CPUBUFFER==0)&&(!cpu_queue.empty())))
        {
            temp=cpu_queue.front();
            cpu_queue.pop();
            fl=1;
            //cout<<"cpu";
        }
        if(((time%DISK1BUFFER==0)&&(!disk1_queue.empty())))
        {
            temp1=disk1_queue.front();
            cpu_queue.push(temp1);
            disk1_queue.pop();
            //cout<<"disk1";
        }
        if(((time%DISK2BUFFER==0)&&(!disk2_queue.empty())))
        {
            temp1=disk2_queue.front();
            cpu_queue.push(temp1);
            disk2_queue.pop();
            //cout<<"disk2";
        }
        if(fl)
        {
            //temp.dequeue();
            switch (temp.dequeue())
            {
            case -1:
                break;
            case 1:
                disk1_queue.push(temp);
                break;
            case 2:
                disk2_queue.push(temp);
                break;
            default:
                break;
            }
        }
        std::chrono::milliseconds timespan(1000);
        std::this_thread::sleep_for(timespan);
    }
    cout<<"\n**********************************************\n";
    cout<<"System State At "<<time<<" Seconds\n";
    if(!cpu_queue.empty()){
        cout<<"CPU Queue\n"<<"Process ID\tProcess Name\n"<<"----------------------------------\n";
        printQueue(cpu_queue);
    }
    else
        cout<<"CPU:Queue Empty\n";
    if(!disk1_queue.empty()){
        cout<<"Disk 1 Queue\n"<<"Process ID\tProcess Name\n"<<"----------------------------------\n";
        printQueue(disk1_queue);
    }
    else
        cout<<"Disk 1:Queue Empty\n";
    if(!disk2_queue.empty()){
        cout<<"Disk 2 Queue\n"<<"Process ID\tProcess Name\n"<<"----------------------------------\n";
        printQueue(disk2_queue);
    }
    else
        cout<<"Disk 2:Queue Empty\n";
    return 0;
}
