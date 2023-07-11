#include <iostream>
#include <algorithm>
#include<iomanip>
#include<climits>
#include<string>
#include <queue> 

using namespace std;

struct process_struct
{
    int pn;
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
}ps[100];


//===========================================================================================================================================
//FCFS


bool comparatorAT(process_struct& a, process_struct& b)
{

    return a.at < b.at;
}

bool comparatorPID(struct process_struct a, struct process_struct b)
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

void FCFS()
{
    int current_time = 0;
    string ganttchcart[4][100];
    int gantt_index = 0;
    int n;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int length_cycle, total_idle_time = 0;
    float cpu_utilization;

    cout << fixed << setprecision(2);

    cout << "Enter total number of processes: ";
    cin >> n;

    while (n <= 0 || !cin)
    {

        cout << "Please enter valid value :  ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> n;

    }
    cout << "total number of processes: " << n;


    int a_value;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process" << i << "Arrival Time: ";

        cin >> a_value;
        while (a_value < 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> a_value;


        }
        cout << "Process" << i << "Arrival Time: " << a_value;
        ps[i].at = a_value;
        ps[i].pid = i;

    }

    int b_value;
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process" << i << "Burst Time: ";

        cin >> b_value;
        while (b_value <= 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> b_value;

        }

        cout << "Process" << i << "Burst Time: " << b_value;
        ps[i].bt = b_value;
    }

    //sort
    sort(&ps[0], &ps[n], comparatorAT);

    //calculation
    for (int i = 0; i < n; i++)
    {

        if (i == 0)
        {
            ps[i].start_time = ps[i].at;

            if (current_time == 0 and ps[i].start_time == 0)
            {
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "| p " + to_string(ps[i].pid);
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;

            }
            else if (current_time == 0 and ps[i].start_time != 0)
            {
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "|IDLE";
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
                current_time = ps[i].start_time - current_time;
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "| p " + to_string(ps[i].pid);
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;

            }

        }
        else
        {


            ps[i].start_time = max(ps[i].at, ps[i - 1].ct);



            if (ps[i].start_time == current_time)
            {
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "| p " + to_string(ps[i].pid);
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
            }
            else if (ps[i].start_time != current_time)
            {


                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "|IDLE";
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
                current_time = ps[i].start_time;
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "| p " + to_string(ps[i].pid);
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;

            }


        }



        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].wt;

        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;

        current_time = ps[i].ct;

        total_idle_time += (i == 0) ? 0 : (ps[i].start_time - ps[i - 1].ct);
    }
    length_cycle = ps[n - 1].ct - ps[0].start_time;
    //sort so that process ID in output comes in Original order (just for interactivity)
    sort(ps, ps + n, comparatorPID);


    cout << "gantt-chcart \n";
    int b;
    for (int a = 0; a < 4; a++)
    {
        for (b = 0; b < current_time; b++)
        {


            cout << ganttchcart[a][b];

        }
        if (b == current_time && a == 1)
        {
            cout << "|";
        }
        if (b == current_time && a == 3)
        {
            cout << current_time;
        }
        cout << endl;
    }


    //Output
    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;



    cout << "\nAverage Turn Around time= " << sum_tat / n;
    cout << "\nAverage Waiting Time= " << sum_wt / n;
}


//=============================================================================================================================================
//SJFP

void SJFP()
{


    string ganttchcart[4][100];
    int gantt_index = 0;
    int n;
    float bt_remaining[100];
    bool is_completed[100] = { false }, is_first_process = true;
    int current_time = 0;
    int completed = 0;;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0, total_idle_time = 0, length_cycle, prev = 0;
    float cpu_utilization;
    int max_completion_time, min_arrival_time;

    cout << fixed << setprecision(2);

    cout << "Enter total number of processes: ";


    cin >> n;
    while (n <= 0 || !cin)
    {

        cout << "Please enter valid value :  ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> n;

    }
    cout << "total number of processes: " << n;




    int a_value;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process" << i << "Arrival Time: ";

        cin >> a_value;
        while (a_value < 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> a_value;


        }
        cout << "Process" << i << "Arrival Time: " << a_value;
        ps[i].at = a_value;
        ps[i].pid = i;

    }

    int b_value;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process" << i << "Burst Time: ";

        cin >> b_value;
        while (b_value <= 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> b_value;

        }

        cout << "Process" << i << "Burst Time: " << b_value;
        ps[i].bt = b_value;
        bt_remaining[i] = ps[i].bt;


    }


    while (completed != n)
    {
        //find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (ps[i].at <= current_time && is_completed[i] == false) {
                if (bt_remaining[i] < minimum) {
                    minimum = bt_remaining[i];;
                    min_index = i;
                }
                if (bt_remaining[i] == minimum) {
                    if (ps[i].at < ps[min_index].at) {
                        minimum = bt_remaining[i];;
                        min_index = i;
                    }
                }
            }
        }




        if (min_index != -1)
        {
            if (gantt_index == 0)
            {
                ganttchcart[1][gantt_index] = "| P " + to_string(ps[min_index].pid);
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
            }
            else
            {
                ganttchcart[1][gantt_index] = "| P " + to_string(ps[min_index].pid);
                if (ganttchcart[1][gantt_index] != ganttchcart[1][gantt_index - 1])
                {
                    ganttchcart[1][gantt_index] = "| P " + to_string(ps[min_index].pid);
                    ganttchcart[0][gantt_index] = "------";
                    ganttchcart[2][gantt_index] = "------";
                    ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                    gantt_index += 1;
                }


            }


        }
        else
        {
            if (gantt_index == 0)
            {
                ganttchcart[1][gantt_index] = "|IDLE";
                ganttchcart[0][gantt_index] = "-------";
                ganttchcart[2][gantt_index] = "-------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
            }
            else
            {
                ganttchcart[1][gantt_index] = "|IDLE";
                if (ganttchcart[1][gantt_index] != ganttchcart[1][gantt_index - 1])
                {
                    ganttchcart[1][gantt_index] = "|IDLE";
                    ganttchcart[0][gantt_index] = "-------";
                    ganttchcart[2][gantt_index] = "-------";
                    ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                    gantt_index += 1;
                }

            }


        }



        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            if (bt_remaining[min_index] == ps[min_index].bt)
            {
                ps[min_index].start_time = current_time;
                total_idle_time += (is_first_process == true) ? 0 : (ps[min_index].start_time - prev);
                is_first_process = false;
            }
            bt_remaining[min_index] -= 1;
            current_time++;
            prev = current_time;
            if (bt_remaining[min_index] == 0)
            {
                ps[min_index].ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
                ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;


                sum_tat += ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                sum_rt += ps[min_index].rt;
                completed++;
                is_completed[min_index] = true;


            }
        }
    }
    //Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, ps[i].ct);
        min_arrival_time = min(min_arrival_time, ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;

    ganttchcart[1][gantt_index] = "";

    cout << "\n \ngantchart : \n";

    int b;
    for (int a = 0; a < 4; a++)
    {
        for (b = 0; b < current_time; b++)
        {


            cout << ganttchcart[a][b];

        }
        if (b == current_time && a == 1)
        {
            cout << "|";
        }
        if (b == current_time && a == 3)
        {
            cout << current_time;
        }
        cout << endl;
    }



    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t " << ps[i].at << "\t\t" << ps[i].bt << "\t " << ps[i].ct << "\t " << ps[i].tat << "\t " << ps[i].wt << "\t " << ps[i].rt << endl;
    cout << endl;

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;


    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    cout << "\nThroughput= " << n / (float)length_cycle;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;

}



//==========================================================================================================================================
//SJFNP

void SJFNP()
{


    string ganttchcart[4][100];
    int gantt_index = 0;
    int n;
    bool is_completed[100] = { false }, is_first_process = true;
    int current_time = 0;
    int completed = 0;
    int sum_tat = 0, sum_wt = 0, sum_rt = 0, total_idle_time = 0, prev = 0, length_cycle;
    float cpu_utilization;
    int max_completion_time, min_arrival_time;

    cout << fixed << setprecision(2);

    cout << "Enter total number of processes: ";


    cin >> n;
    while (n <= 0 || !cin)
    {

        cout << "Please enter valid value :  ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> n;

    }
    cout << "total number of processes: " << n;




    int a_value;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process" << i << "Arrival Time: ";

        cin >> a_value;
        while (a_value < 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> a_value;


        }
        cout << "Process" << i << "Arrival Time: " << a_value;
        ps[i].at = a_value;
        ps[i].pid = i;

    }

    int b_value;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process" << i << "Burst Time: ";

        cin >> b_value;
        while (b_value <= 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> b_value;

        }

        cout << "Process" << i << "Burst Time: " << b_value;
        ps[i].bt = b_value;

    }


    while (completed != n)
    {
        //find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (ps[i].at <= current_time && is_completed[i] == false) {
                if (ps[i].bt < minimum) {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if (ps[i].bt == minimum) {
                    if (ps[i].at < ps[min_index].at) {
                        minimum = ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }




        if (min_index != -1)
        {
            if (gantt_index == 0)
            {
                ganttchcart[1][gantt_index] = "| P " + to_string(ps[min_index].pid);
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
            }
            else
            {
                ganttchcart[1][gantt_index] = "| P " + to_string(ps[min_index].pid);
                if (ganttchcart[1][gantt_index] != ganttchcart[1][gantt_index - 1])
                {
                    ganttchcart[1][gantt_index] = "| P " + to_string(ps[min_index].pid);
                    ganttchcart[0][gantt_index] = "------";
                    ganttchcart[2][gantt_index] = "------";
                    ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                    gantt_index += 1;
                }


            }


        }
        else
        {
            if (gantt_index == 0)
            {
                ganttchcart[1][gantt_index] = "|IDLE";
                ganttchcart[0][gantt_index] = "-------";
                ganttchcart[2][gantt_index] = "-------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;
            }
            else
            {
                ganttchcart[1][gantt_index] = "|IDLE";
                if (ganttchcart[1][gantt_index] != ganttchcart[1][gantt_index - 1])
                {
                    ganttchcart[1][gantt_index] = "|IDLE";
                    ganttchcart[0][gantt_index] = "-------";
                    ganttchcart[2][gantt_index] = "-------";
                    ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                    gantt_index += 1;
                }

            }


        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
            ps[min_index].rt = ps[min_index].wt;
            // ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;

            sum_tat += ps[min_index].tat;
            sum_wt += ps[min_index].wt;
            sum_rt += ps[min_index].rt;
            total_idle_time += (is_first_process == true) ? 0 : (ps[min_index].start_time - prev);

            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].ct;
            prev = current_time;
            is_first_process = false;
        }
    }

    //Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, ps[i].ct);
        min_arrival_time = min(min_arrival_time, ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;

    ganttchcart[1][gantt_index] = "";

    cout << "\n \ngantchart : \n";

    int b;
    for (int a = 0; a < 4; a++)
    {
        for (b = 0; b < current_time; b++)
        {


            cout << ganttchcart[a][b];

        }
        if (b == current_time && a == 1)
        {
            cout << "|";
        }
        if (b == current_time && a == 3)
        {
            cout << current_time;
        }
        cout << endl;
    }


    //Output
    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct 
        << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    cout << "\nThroughput= " << n / (float)length_cycle;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;

}

//=============================================================================================================================================
//RR


void RR()
{

    int gantt_index = 0;
    string ganttchcart[4][100];
    int n, index;
    int cpu_utilization;
    queue<int> q;
    bool visited[100] = { false }, is_first_process = true;
    int current_time = 0;
    int max_completion_time;
    int completed = 0, tq, total_idle_time = 0, length_cycle;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    cout << fixed << setprecision(2);


    cout << "Enter total number of processes: ";
    cin >> n;
    while (n <= 0 || !cin)
    {

        cout << "Please enter valid value :  ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> n;

    }
    cout << "total number of processes: " << n;


    int a_value;
    for (int i = 0; i < n; i++)
    {

        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> a_value;
        while (a_value < 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> a_value;


        }
        cout << "Process" << i << "Arrival Time: " << a_value;
        ps[i].at = a_value;
        ps[i].pid = i;
        ps[i].pn = i;

    }

    int b_value;
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> b_value;
        while (b_value <= 0 || !cin)
        {

            cout << "Please enter valid value :  ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> b_value;

        }

        cout << "Process" << i << "Burst Time: " << b_value;
        ps[i].bt = b_value;
        ps[i].bt_remaining = ps[i].bt;
    }

    cout << "\nEnter time quanta: ";
    cin >> tq;
    
    while (tq <= 0 || !cin)
    {

        cout << "Please enter valid value :  ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> tq;

    }
    cout << "time quanta: " << tq<<"\n";

    //sort structure on the basis of Arrival time in increasing order
    sort(&ps[0], &ps[n], comparatorAT);

    q.push(0);
    visited[0] = true;

    while (completed != n)
    {
        index = q.front();
        q.pop();

        if (ps[index].bt_remaining == ps[index].bt)
        {
            ps[index].start_time = max(current_time, ps[index].at);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;

            if (current_time == 0 && ps[index].start_time > 0)
            {
                ganttchcart[0][gantt_index] = "------";
                ganttchcart[1][gantt_index] = "|IDLE";
                ganttchcart[2][gantt_index] = "------";
                ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                gantt_index += 1;

            }




            current_time = ps[index].start_time;
            is_first_process = false;

        }

        if (ps[index].bt_remaining - tq > 0)
        {

            ganttchcart[0][gantt_index] = "------";
            ganttchcart[1][gantt_index] = "| p" + to_string(ps[index].pn) + " ";
            ganttchcart[2][gantt_index] = "------";
            ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
            gantt_index += 1;

            ps[index].bt_remaining -= tq;
            current_time += tq;


        }
        else
        {

            ganttchcart[0][gantt_index] = "------";
            ganttchcart[1][gantt_index] = "| p" + to_string(ps[index].pn) + " ";
            ganttchcart[2][gantt_index] = "------";
            ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
            gantt_index += 1;
            current_time += ps[index].bt_remaining;


            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }


        //check which new Processes needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        //check if Process on CPU needs to be pushed to Ready Queue
        if (ps[index].bt_remaining > 0)
            q.push(index);

        //if queue is empty, just add one process from list, whose remaining burst time > 0
        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    q.push(i);
                    visited[i] = true;

                    ganttchcart[0][gantt_index] = "------";
                    ganttchcart[1][gantt_index] = "|IDLE";
                    ganttchcart[2][gantt_index] = "------";
                    ganttchcart[3][gantt_index] = to_string(current_time) + "    ";
                    gantt_index += 1;

                    break;
                }
            }
        }
    } //end of while

    //Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;

    for (int i = 0; i < n; i++)
        max_completion_time = max(max_completion_time, ps[i].ct);

    length_cycle = max_completion_time - ps[0].at;  //ps[0].start_time; 

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    //sort so that process ID in output comes in Original order (just for interactivity- Not needed otherwise)  
    sort(ps, ps + n, comparatorPID);

    cout << "gantt-chcart \n";
    int b;
    for (int a = 0; a < 4; a++)
    {
        for (b = 0; b < current_time; b++)
        {


            cout << ganttchcart[a][b];

        }
        if (b == current_time && a == 1)
        {
            cout << "|";
        }
        if (b == current_time && a == 3)
        {
            cout << current_time;
        }
        cout << endl;
    }

    //Output
    cout << "\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" 
        << ps[i].start_time << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    cout << "\nThroughput= " << n / (float)length_cycle;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;

}


//=============================================================================================================================================




int main()
{
    int no_program = 0;

    cout << "1.FCFS :\n";
    cout << "2.SJFNP :\n";
    cout << "3.SJFP :\n";
    cout << "4.RR :\n";


    cout << "Chose Form 1-4 : ";
    cin >> no_program;

    while (no_program <= 0 || !cin || no_program > 4)
    {

        cout << "Please enter valid value :  ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> no_program;

    }


    if (no_program == 1)
    {
        FCFS();
    }
    else if(no_program == 2)
    {
        SJFNP();
    }
    else if (no_program == 3)
    {
        SJFP();
    }
    else if (no_program == 4)
    {
        RR();
    }


    
    return 0;


}


