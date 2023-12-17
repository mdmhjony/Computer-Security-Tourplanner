#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int brusttime;
    int remaingtime;
    int arrivaltime;
    int turnaroundtime;
    int waitingtime;
    int responsetime;  
};

float getRandomNumber(float a, float b) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> distribution(a, b);
    return distribution(gen);
}

void calculateResult(const vector<Process>& processes) {
    int totalProcesses = processes.size();
    float totalturnaroundtime = 0;
    float totalwaitingtime = 0;
    float totalresponsetime = 0;  
    int maxturnaorundtime = INT_MIN;
    int maxwatingtime = INT_MIN;
    int maxresponsetime = INT_MIN;  
    int maxturnaroundtimeprocessid = -1;
    int maxwatingtimeprocessid = -1;
    int maxresponsetimeprocessid = -1;  

    for (const auto& process : processes) {
        totalturnaroundtime += process.turnaroundtime;
        totalwaitingtime += process.waitingtime;
        totalresponsetime += process.responsetime;  

        if (process.turnaroundtime > maxturnaorundtime) {
            maxturnaorundtime = process.turnaroundtime;
            maxturnaroundtimeprocessid = process.id;
        }

        if (process.waitingtime > maxwatingtime) {
            maxwatingtime = process.waitingtime;
            maxwatingtimeprocessid = process.id;
        }

        if (process.responsetime > maxresponsetime) {  
            maxresponsetime = process.responsetime;
            maxresponsetimeprocessid = process.id;
        }
    }

    float avgturnaroundtime = totalturnaroundtime / totalProcesses;
    float avgwatingtime = totalwaitingtime / totalProcesses;
    float avgresponsetime = totalresponsetime / totalProcesses;  

    cout << "Average Turnaround Time: " << avgturnaroundtime << endl;
    cout << "Average Waiting Time: " << avgwatingtime << endl;
    cout << "Average Response Time: " << avgresponsetime << endl;  
    cout << "Max TurnAround Time: " << maxturnaorundtime << " Process Id: " << maxturnaroundtimeprocessid << endl;
    cout << "Max Waiting Time: " << maxwatingtime << " Process Id: " << maxwatingtimeprocessid << endl;
    cout << "Max Response Time: " << maxresponsetime << " Process Id: " << maxresponsetimeprocessid << endl; 
}

int main() {
    float p;
    int n, l;

    cout << "Enter probability P(range 0 to 1): ";
    cin >> p;
    cout << "Enter max no of process n: ";
    cin >> n;
    cout << "Enter max burst time l: ";
    cin >> l;

    queue<Process> readyqueue;
    vector<Process> processes;
    int curTime = 0;
    int step = 50;
    int processid = 0;

    float newprocessprobability;
    for (int i = 0; i <= step; i++) {
        newprocessprobability = getRandomNumber(0.0f, 1.0f);
        if (newprocessprobability >= p) {
            int numofprocess = getRandomNumber(1, n);
            for (int j = 0; j < numofprocess; j++) {
                Process newProcess;
                newProcess.id += processid;
                newProcess.brusttime = getRandomNumber(1, l);
                newProcess.remaingtime = newProcess.brusttime;
                newProcess.arrivaltime = curTime;
                newProcess.waitingtime = 0;
                newProcess.turnaroundtime = 0;
                newProcess.responsetime = 0;  
                readyqueue.push(newProcess);
            }
        }

        if (!readyqueue.empty()) {
            Process curProcess = readyqueue.front();
            readyqueue.pop();
            int timequantum = 1;
            if (curProcess.remaingtime > timequantum) {
                curTime += timequantum;
                curProcess.remaingtime -= timequantum;
                curProcess.responsetime = curTime - curProcess.arrivaltime;  
                readyqueue.push(curProcess);
            } else {
                curTime += curProcess.remaingtime;
                curProcess.turnaroundtime = curTime - curProcess.arrivaltime;
                curProcess.waitingtime = curProcess.turnaroundtime - curProcess.brusttime;
                curProcess.responsetime = curProcess.turnaroundtime;  
                processes.push_back(curProcess);
            }
        } else {
            curTime += 1;
        }
    }

    calculateResult(processes);

    return 0;
}
