#include<stdio.h>
#include<iostream>
#include<math.h>

using namespace std;

class Point2D
{
    double x_co_ordinate;
    double y_co_ordinate;

public:
    Point2D()   {x_co_ordinate = 0; y_co_ordinate = 0;}
    Point2D(double x,double y)  {x_co_ordinate = x; y_co_ordinate = y;}
    double get_x()   {return x_co_ordinate;}
    double get_y()   {return y_co_ordinate;}
    double distance(Point2D point)
    {
        return sqrt(((this->x_co_ordinate - point.get_x())*(this->x_co_ordinate - point.get_x())) + ((this->y_co_ordinate - point.get_y())*(this->y_co_ordinate - point.get_y())));
    }
    void print()
    {
        cout<<"("<<this->get_x()<<","<<this->get_y()<<")"<<endl;
    }
};

Point2D* sort_x(Point2D* not_sorted,int size_not_sorted)
{

    int size_incoming = size_not_sorted;
    Point2D* temp = new Point2D[size_incoming];
    temp = not_sorted;
    //temp[4].print();
    for(int i=0 ; i<size_incoming ; i++)
    {
        for(int j=0 ; j<size_incoming-1 ; j++)
        {
            if(temp[j].get_x() > temp[j+1].get_x())
            {
                Point2D now = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = now;
                //temp[j].print();
            }
        }
    }
    //temp[0].print();
    Point2D* another = new Point2D[size_incoming];
    for(int k=0; k<size_incoming;k++)
        another[k] = temp[k];
    return another;

}

Point2D* sort_y(Point2D* not_sorted,int size_not_sorted)
{
    int size_incoming = size_not_sorted;
    Point2D* temp = new Point2D[size_incoming];
    temp = not_sorted;
    for(int i=0 ; i<size_incoming ; i++)
    {
        for(int j=0 ; j<size_incoming-1 ; j++)
        {
            if(temp[j].get_y() > temp[j+1].get_y())
            {
                Point2D now = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = now;
            }
        }
    }

    Point2D* another = new Point2D[size_incoming];
    for(int k=0; k<size_incoming;k++)
        another[k] = temp[k];
    return another;
}

Point2D* Closest_pair_rec(Point2D* P_x,Point2D* P_y,int size_P)
{
    if(size_P <= 3)
    {
        if(size_P == 2)
            return P_x;
        double distance_1 = P_x[0].distance(P_x[1]);
        double distance_2 = P_x[0].distance(P_x[2]);
        double distance_3 = P_x[1].distance(P_x[2]);

        if(distance_1 <= distance_2 && distance_1 <= distance_3)
        {
            Point2D* then = new Point2D[2];
            then[0] = P_x[0];
            then[1] = P_x[1];
            return then;
        }
        if(distance_2 <= distance_1 && distance_2 <= distance_3)
        {
            Point2D* then = new Point2D[2];
            then[0] = P_x[0];
            then[1] = P_x[2];
            return then;
        }
        if(distance_3 <= distance_2 && distance_3 <= distance_1)
        {
            Point2D* then = new Point2D[2];
            then[0] = P_x[1];
            then[1] = P_x[2];
            return then;
        }

    }
    int number = size_P;
    int first_half = number/2;
    //cout<<first_half<<endl;
    int second_half = number - first_half;
    //cout<<second_half<<endl;
    Point2D* Q = new Point2D[first_half];
    Point2D* R = new Point2D[second_half];
    int i;
    for(i=0 ; i<first_half ; i++)
    {
        Q[i] = P_x[i];
        //Q[i].print();
    }

    for(int j=0 ; j<second_half ; j++)
    {
        R[j] = P_x[i];
        i++;
    }

    Point2D* Q_x = new Point2D[first_half];
    Point2D* Q_y = new Point2D[first_half];
    Point2D* R_x = new Point2D[second_half];
    Point2D* R_y = new Point2D[second_half];

    Q_x = sort_x(Q,first_half);
    Q_y = sort_y(Q,first_half);
    R_x = sort_x(R,second_half);
    R_y = sort_y(R,second_half);

    Point2D* for_q = new Point2D[2];
    Point2D* for_r = new Point2D[2];

    for_q = Closest_pair_rec(Q_x,Q_y,first_half);
    for_r = Closest_pair_rec(R_x,R_y,second_half);
    //for_r[0].print();
    //for_r[1].print();
    //for_q[0].print();
    //for_q[1].print();


    double distance_q = for_q[0].distance(for_q[1]);
    double distance_r = for_r[0].distance(for_r[1]);
    double del;
    if(distance_q < distance_r)
        del = distance_q;
    else
        del = distance_r;
    //cout<<del<<endl;
    double max_x_of_q = Q_x[first_half-1].get_x();
    //cout<<max_x_of_q<<endl;

    Point2D* S = new Point2D[number];
    int for_S = 0;
    for(int k=0 ; k<number ; k++)
    {
        if(fabs(P_x[k].get_x() - max_x_of_q) < del)
        {
            S[for_S] = P_x[k];
            for_S++;
        }
    }

    int size_S = for_S;
    Point2D* S_y = new Point2D[size_S];
    S_y = sort_y(S,size_S);
    double min_for_S = S_y[0].distance(S_y[1]);
    Point2D* min_in_S = new Point2D[2];
    min_in_S[0] = S_y[0];
    min_in_S[1] = S_y[1];
    for(int g=0 ; g<size_S-1 ; g++)
    {
        for(int h=g+1 ; h<size_S ; h++)
        {
            if(S_y[g].distance(S_y[h]) < min_for_S)
            {
                min_for_S = S_y[g].distance(S_y[h]);
                min_in_S[0] = S_y[g];
                min_in_S[1] = S_y[h];
            }
        }
    }

    if(min_for_S < del)
        return min_in_S;
    else if(distance_q < distance_r)
        return for_q;
    else
        return for_r;


}

Point2D* Closest_pair(Point2D* P,int size_P)
{
    int number = size_P;
    cout<<number<<endl;
    Point2D* P_x = new Point2D[number];
    Point2D* P_y = new Point2D[number];
    P_x = sort_x(P,number);
    P_y = sort_y(P,number);

    return Closest_pair_rec(P_x,P_y,number);
}

int main()
{
    freopen("input.txt","r",stdin);

    int n;
    cin>>n;
    Point2D* main_list;
    main_list = new Point2D[n];

    for(int i=0 ; i<n ; i++)
    {
        double x,y;
        cin>>x;
        cin>>y;
        Point2D temp(x,y);
        main_list[i] = temp;
    }
    Point2D* the_pair = new Point2D[2];
    the_pair = Closest_pair(main_list,n);

    the_pair[0].print();
    the_pair[1].print();

    cout<<the_pair[0].distance(the_pair[1])<<endl;
}
