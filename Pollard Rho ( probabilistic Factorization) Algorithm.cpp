
//This is an algorithm For Finding a Divisor of a Number . It is a probabilistic algorithm . 
//Using BirthDay paradox to explain the probability 

//And its is a good algorthm for finding a divisior of a Large Number such as N >= 1e15 [ which requres less than 1e6 moves  ]
                                            [There is a 90% plus probability that using 1e6 Random number we shall get a divisor]

  
int cnt = 0;
int Pollard_Rho(int N)
{
        if(N==1)
        {
                return N;
        }
        if(N%2==0)
        {
                return 2;
        }

        srand(time(NULL));

        int x = (rand()%(N-2))+2;
        
        int y = x;

        int d = 1;

        int c = (rand()%(N-1))+1;

        while(d==1)
        {
                //Tortoise : Slow pointer
                x = (((x%N)*(x%N))%N + c)%N;

                //Hare : Fast Pointer
                y = (((y%N)*(y%N))%N + c)%N;
                y = (((y%N)*(y%N))%N + c)%N;

                d = __gcd( abs(x-y) , N);

                ++cnt;

                if(d==N)  // x mod N = y mod N . which means [ abs(x-y) = N ] eta hole Notun kore abar algorithm chalate hobe 
                {
                        //Mane Pollard rho loop e pore gese
                        
                        //Notun iteration dorkar hobe 
                        return Pollard_Rho(N);
                }


        }

        return d;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int N = 223007;

        N = N*N*N;
        //cin>>N;

        int d = Pollard_Rho(N);

        cout<<"The Number : "<<N<<endl;

        cout<<"Number of Move : "<<cnt<<endl;

        cout<<"Divisor: "<<d<<endl;

        cout<<"Confirmation : "<<(N%d)<<endl;

        return 0;




}
