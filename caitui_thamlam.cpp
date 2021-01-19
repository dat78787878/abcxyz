
#include <iostream>
#include <fstream>
using namespace std;

#define MAX 100

struct Obj
{
    int id; //luu id vat sau khi sx
    int Weight, Value;
    float RealValue; //gia tri thuc bang gia tri chia do nang
    int SoLuong; //so lan vat nay duoc chon
};

int W[MAX + 1], V[MAX + 1];
int n; // so luong do vat
int w; //khoi luong cua balo
int total = 0, totalValue = 0, totalWeight = 0;
Obj ob[MAX + 1];

void Input()
{
    ifstream infile;
    infile.open("input3.txt");
    infile >> n >> w;
    cout << n << " " << w << "\n";
    for (int i = 1; i <= n; i++)
    {
        infile >> ob[i].Weight >> ob[i].Value; //trong luong va gia tri cua tung vat
        cout << "#" << i << ": " << ob[i].Weight << " " << ob[i].Value << "\n";
    }
    infile.close();
}

//tinh gia tri
void CalculateRealValue()
{
    for (int i = 1; i <= n; i++)
    {
        ob[i].id = i; // set id
        ob[i].RealValue = (float)ob[i].Value / (float)ob[i].Weight;
    }
}

//sx do vat theo gia tri
void SortObj(int left, int right)
{
    float pivot = ob[(left + right) / 2].RealValue;
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (ob[i].RealValue > pivot)
            i++;
        while (ob[j].RealValue < pivot)
            j--;

        if (i <= j)
        {
            Obj tmp = ob[i];
            ob[i] = ob[j];
            ob[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        SortObj(left, j);
    if (i < right)
        SortObj(i, right);
}

void GreedyPick(int W)
{
    for (int i = 1; i <= n; i++)
    {
        //cout<<ob[i].id<<" ~ "<<ob[i].Weight<<" ~ "<<ob[i].Value<<" ~ "<<ob[i].RealValue<<endl; // debug
        if (W >= ob[i].Weight)
        {
            /* uncomment v?i bài lo?i 2 */
            //ob[i].SoLuong = W / ob[i].Weight;
            //W -= ob[i].SoLuong * ob[i].Weight;

            /* uncomment v?i bài lo?i 1 */
            ob[i].SoLuong = 1;
            W -= ob[i].Weight;

            total += ob[i].SoLuong;
            totalValue += ob[i].Value * ob[i].SoLuong;
            totalWeight += ob[i].SoLuong * ob[i].Weight;
        }
    }
}

void Print()
{
    cout << "\nTong so vat da lay: " << total;
    cout << "\nGia tri lon nhat co the lay: " << totalValue;
    cout << "\nKhoi luong da su dung: " << totalWeight;
    cout << "\nCac vat da lay [stt (so luong)] : ";
    for (int i = 1; i <= n; i++)
    {
        if (ob[i].SoLuong > 0)
        {
            cout << ob[i].id << " (" << ob[i].SoLuong << ")  "; // chon vat i - so luong ob[i].SoLuong
        }
    }
}

int main()
{
    Input();
    CalculateRealValue();
    SortObj(1, n);
    GreedyPick(w);
    Print();

    return 0;
}
