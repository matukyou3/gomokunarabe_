#include<iostream>
#include<string>


class player
{
    private:
        int _num;
        std::string _name;
    public:
        player(int num, std::string name)
        {
            _num = num;
            _name = name;
        }
        int get_num()
        {
            return _num;
        }
        std::string get_name()
        {
            return _name;
        }
};

class board
{
    private:
        int frame[15][15];
        char goishi[3]={'+', 'O','X'};
        std::string sepa ="-----------------------------------";
        
    public:
        board()
        {
            init();
        }
        void init()
        {
            for(int i=1;i<14;++i)
            {
                for(int j=1;j<14;++j)
                {
                    frame[i][j] =0;
                }
            }

            for(int i=0;i<15;++i)
            {
                frame[i][0]=99;
                frame[0][i]=99;
                frame[14][i]=99;
                frame[i][14]=99;
            }
        }

        void set_goishi(int player, int raw, int col)
        {
            frame[raw][col]=player;
        }

        int get_goishi(int raw,int col)
        {
            return frame[raw][col];
        }

        void display()
        {
            std::cout<<sepa<<std::endl;
            for(int i=1;i<13;++i)
            {
                for(int j=1;j<13;++j)
                {
                    std::cout<<goishi[frame[i][j]];
                    std::cout<< "  ";
                }
                std::cout<<std::endl;
            }
            std::cout<<sepa<<std::endl;
        }


        int judge(int player, int raw, int col,int x, int y)
        {
            int res=0;
            int a=0, b=0;
            while(frame[raw +b][col+a]==player)
            {
                res= res +1;
                a = a +x;
                b = b +y;
            }
            return res;
        }
};

class game
{
    private:
        int tesuu;
        bool teban;//true -> sente, false -> gote 
        board bd;      
    public:
        game()
        {
            init();
        }

        void init()
        {
            teban = true;
            tesuu =0;
            bd.init();
            std::cout<<"Game Start!!!!"<<std::endl;
        }

        bool get_teban()
        {
            return teban;
        }

        bool check(int raw,int col)
        {
            return bd.get_goishi(raw,col)==0;
        }
       
        void put_goishi(int player,int raw,int col)
        {
            bd.set_goishi(player,raw,col);
        }

        void display()
        {
            bd.display();
        }

        bool judge(int player, int raw, int col)
        {
            int yoko = bd.judge(player, raw, col,-1, 0) + bd.judge(player, raw, col, 1, 0) -1;
            int tate = bd.judge(player, raw, col, 0, 1) + bd.judge(player, raw, col, 0, -1) -1;
            int lurd = bd.judge(player, raw, col, 1, 1) + bd.judge(player, raw, col, -1, -1) -1;
            int ldru = bd.judge(player, raw, col, 1, -1) + bd.judge(player, raw, col, -1, 1) -1;

            return yoko >=5 || tate >=5 || lurd >= 5|| ldru >=5;
        }
        void next_teban()
        {
            teban = !teban;
        }


};

int main()
{
    int player_num;
    int raw,col;
    game gm;

    std::string player1_name;
    std::string player2_name;
    std::cout<<"player1 Name is :";
    std::cin>>player1_name;
    std::cout <<"player2 Name is :";
    std::cin>>player2_name;
    player player1(1, player1_name);
    player player2(2, player2_name);
    
    while(1)
    {
        if(gm.get_teban())
        {
            std::cout<<player1.get_name() + " put goishi O"<<std::endl;
            player_num = player1.get_num();
        }
        else
        {
            std::cout<<player2.get_name() + " put goishi X"<<std::endl;
            player_num = player2.get_num();       
        }
        
        while(1)
        {
            std::cin>>raw>>col;
            if(gm.check(raw,col))
            {
                gm.put_goishi(player_num,raw,col);
                break;
            }
            std::cout<<"failed \n Put again"<<std::endl;
        }

        gm.display();

        if(gm.judge(player_num, raw, col))
        {
            if(gm.get_teban())
            {
                std::cout << player1.get_name() + "Win!!!"<<std::endl;
                break;
            }
            else
            {
                std::cout<< player2.get_name() + "Win!!"<<std::endl;
                break;
            }
           
        }
         gm.next_teban();
         
    }

    
    return 0;
}