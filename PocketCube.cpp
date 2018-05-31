/*
 * This file contain functions definitions
 * needed to solve 2*2*2 cube with minimum number
 * of moves with maximum 11 moves for
 * any possible configuration
 *
 * author -:
 * Amarjeet Singh Kapoor
 * Govind Sharma
 */


#include"PocketCube.h"

using namespace std;

//list of moves
string moves[18]={"U","Ui","U2","D","Di","D2","R","Ri","R2","L","Li",
                    "L2","F","Fi","F2", "B","Bi","B2"};

//list of colors
char color[6]={'Y','G','W','B','O','R'};

/*
 * This is constructure for initializing
 * a cube state i.e. make cube
 */

CubeState::CubeState(){
    for(int i=0, k=0; i<24; i=i+4, k++){
        for(int j=0;j<4;j++)
            configuration[i+j]=color[k]; // assign color to each piece.  
        }
}

/* Prints the configuration in which
 * cube is
 */
void CubeState::printMe(){
    for(int i=0;i<24;i++)
        cout<<configuration[i]<<"";
    cout<<endl;
}

void test_scope(CubeState cube)
{
	queue<CubeState> Q;
	int level, max = -1;
	unsigned long long code, org = -1;
	CubeState node, temp;
	set <unsigned long long> cube_set;
	
	code = code_generator(cube);
	cube_set.insert(code);
	Q.push(cube);
	bool check = true;
	while(!Q.empty()) {
		node = Q.front();
		Q.pop();
		for(int i = 0; i < 18; i++) {
			temp = generate_new(node, i);
			code = code_generator(temp);
			if (code == 8811212735103670767) {
				temp.printMe();	
				give_solution(temp);
				cout << moves[i] << endl;
				cout << endl;
			}
			if(cube_set.find(code) != cube_set.end()) {
				/*if (org == -1) {
					org = code;
					cout << code << endl;
				}
				if (code == org)
					temp.printMe();*/
				continue;
			}
			else {
				cube_set.insert(code);
				temp.parent.push_back(i);
				level = temp.parent.size();
				if (level > max) {
					max = level;
					//cout << max << ": "; temp.printMe(); cout << " : " << code_generator(temp) << " " << endl;
					if (level == 17) {
						//give_solution(temp);
					}
				}
				/*if (level > 11) {
					temp.printMe();
					check = false;
					break;
				}*/
				Q.push(temp);
			}
		} 
	}
	//cout << cube_set.size();
}
/*
 * This mehtod is used for
 * solving cube when called by
 * main function and given scrambled
 * state
 */
int cube_solving(CubeState cube ){
    queue<CubeState> Q;
    int level; //level of the graph of configurations
    unsigned long long code; //code to uniquly identify the cube state
    CubeState node ,temp; //temporapy cube states.
    set <unsigned long long> cube_set; 
    // displaying resulting answer
    cout<<"Configuration after scramble:\n\n";
    cube.printMe();
    //Putting initial node in queue
    cout<<"\n\n Solved sequence:\n\n";
    code=code_generator(cube);
    cube_set.insert(code);
    Q.push(cube);
    clock_t start ,end;
    start =clock();
    //move to neighour nodes
    while(!Q.empty()){
        //checking node whether it is answer
        if(check(&Q.back())){
            give_solution(Q.back());
            break;
        }
        // getting node whose neighbour had to be processed
        node=Q.front();
        Q.pop();
        // processing all the neighbour of node
        for(int i=0; i<18; i++){
            //getting new node and associated code
            temp=generate_new(node, i);
            code=code_generator(temp);
            //checking if cube_state is already processed
            if(cube_set.find(code)!=cube_set.end())
                continue;
            else{

                //inserting new node in and set
                cube_set.insert(code);
                temp.parent.push_back(i);
                /*level=temp.parent.size();

                // terminating if did not get node
                if(level>11){
                    cout<<"Invalid Configuration\n";
                    return 0;
                }
                */

                // pushing element in queue
                Q.push(temp);
            }

            //checking cube_state for answer
            if(check(&Q.back()))
                break;
        }
    }

    end=clock();
    cout<<"time taken is"<<(end-start)/CLOCKS_PER_SEC<<"sec"<<endl;
    return 0;
}


/*
 * This function produce possible new configuration
 * for given move and from given state of Cube.
 */
CubeState generate_new(CubeState obj, int i){

    //generate new state based on number of move
    char temp1, temp2;
    switch(i){

        case 0:{

            // configuration for U move
            temp1=obj.configuration[14];
            temp2=obj.configuration[15];
            obj.configuration[15]=obj.configuration[22];
            obj.configuration[14]=obj.configuration[21];
            obj.configuration[21]=obj.configuration[4];
            obj.configuration[22]=obj.configuration[5];
            obj.configuration[4]=obj.configuration[19];
            obj.configuration[5]=obj.configuration[16];
            obj.configuration[19]=temp1;
            obj.configuration[16]=temp2;
            temp1=obj.configuration[0];
            obj.configuration[0]=obj.configuration[3];
            obj.configuration[3]=obj.configuration[2];
            obj.configuration[2]=obj.configuration[1];
            obj.configuration[1]=temp1;
            break;
        }

        case 1:{

            //congiuration for Ui move
            temp1=obj.configuration[14];
            temp2=obj.configuration[15];
            obj.configuration[14]=obj.configuration[19];
            obj.configuration[15]=obj.configuration[16];
            obj.configuration[16]=obj.configuration[5];
            obj.configuration[19]=obj.configuration[4];
            obj.configuration[4]=obj.configuration[21];
            obj.configuration[5]=obj.configuration[22];
            obj.configuration[21]=temp1;
            obj.configuration[22]=temp2;
            temp1=obj.configuration[0];
            obj.configuration[0]=obj.configuration[1];
            obj.configuration[1]=obj.configuration[2];
            obj.configuration[2]=obj.configuration[3];
            obj.configuration[3]=temp1;
            break;
        }
        case 2:{

             //congiuration for U2 move
            temp1=obj.configuration[14];
            temp2=obj.configuration[15];
            char temp3=obj.configuration[22];
            char temp4=obj.configuration[21];
            obj.configuration[14]=obj.configuration[4];
            obj.configuration[15]=obj.configuration[5];
            obj.configuration[21]=obj.configuration[19];
            obj.configuration[22]=obj.configuration[16];
            obj.configuration[19]=temp4;
            obj.configuration[16]=temp3;
            obj.configuration[4]=temp1;
            obj.configuration[5]=temp2;
            temp1=obj.configuration[0];
            temp2=obj.configuration[1];
            obj.configuration[0]=obj.configuration[2];
            obj.configuration[1]=obj.configuration[3];
            obj.configuration[2]=temp1;
            obj.configuration[3]=temp2;
            break;
        }
        case 3:{

            //congiuration for D move
            temp1=obj.configuration[12];
            temp2=obj.configuration[13];
            obj.configuration[12]=obj.configuration[17];
            obj.configuration[13]=obj.configuration[18];
            obj.configuration[17]=obj.configuration[6];
            obj.configuration[18]=obj.configuration[7];
            obj.configuration[6]=obj.configuration[23];
            obj.configuration[7]=obj.configuration[20];
            obj.configuration[23]=temp1;
            obj.configuration[20]=temp2;
            temp1=obj.configuration[8];
            obj.configuration[8]=obj.configuration[11];
            obj.configuration[11]=obj.configuration[10];
            obj.configuration[10]=obj.configuration[9];
            obj.configuration[9]=temp1;
            break;
        }
        case 4:{

            //congiuration for Di move
            temp1=obj.configuration[12];
            temp2=obj.configuration[13];
            obj.configuration[12]=obj.configuration[23];
            obj.configuration[13]=obj.configuration[20];
            obj.configuration[23]=obj.configuration[6];
            obj.configuration[20]=obj.configuration[7];
            obj.configuration[6]=obj.configuration[17];
            obj.configuration[7]=obj.configuration[18];
            obj.configuration[17]=temp1;
            obj.configuration[18]=temp2;
            temp1=obj.configuration[8];
            obj.configuration[8]=obj.configuration[9];
            obj.configuration[9]=obj.configuration[10];
            obj.configuration[10]=obj.configuration[11];
            obj.configuration[11]=temp1;
            break;
        }
        case 5:{

                //congiuration for D2 move
            temp1=obj.configuration[12];
            temp2=obj.configuration[13];
            char temp3=obj.configuration[18];
            char temp4=obj.configuration[17];
            obj.configuration[12]=obj.configuration[6];
            obj.configuration[13]=obj.configuration[7];
            obj.configuration[18]=obj.configuration[20];
            obj.configuration[17]=obj.configuration[23];
            obj.configuration[6]=temp1;
            obj.configuration[7]=temp2;
            obj.configuration[20]=temp3;
            obj.configuration[23]=temp4;
            temp1=obj.configuration[8];
            temp2=obj.configuration[9];
            obj.configuration[8]=obj.configuration[10];
            obj.configuration[9]=obj.configuration[11];
            obj.configuration[10]=temp1;
            obj.configuration[11]=temp2;
            break;
        }
        case 6:{

            //congiuration for R move
            temp1=obj.configuration[14];
            temp2=obj.configuration[13];
            obj.configuration[14]=obj.configuration[2];
            obj.configuration[13]=obj.configuration[1];
            obj.configuration[2]=obj.configuration[6];
            obj.configuration[1]=obj.configuration[5];
            obj.configuration[6]=obj.configuration[10];
            obj.configuration[5]=obj.configuration[9];
            obj.configuration[10]=temp1;
            obj.configuration[9]=temp2;
            temp1=obj.configuration[16];
            obj.configuration[16]=obj.configuration[19];
            obj.configuration[19]=obj.configuration[18];
            obj.configuration[18]=obj.configuration[17];
            obj.configuration[17]=temp1;
            break;
        }
        case 7:{

            //congiuration for Ri move
            temp1=obj.configuration[14];
            temp2=obj.configuration[13];
            obj.configuration[14]=obj.configuration[10];
            obj.configuration[13]=obj.configuration[9];
            obj.configuration[10]=obj.configuration[6];
            obj.configuration[9]=obj.configuration[5];
            obj.configuration[6]=obj.configuration[2];
            obj.configuration[5]=obj.configuration[1];
            obj.configuration[2]=temp1;
            obj.configuration[1]=temp2;
            temp1=obj.configuration[16];
            obj.configuration[16]=obj.configuration[17];
            obj.configuration[17]=obj.configuration[18];
            obj.configuration[18]=obj.configuration[19];
            obj.configuration[19]=temp1;
            break;
        }
        case 8:{

            //congiuration for R2 move
            temp1=obj.configuration[14];
            temp2=obj.configuration[13];
            char temp3=obj.configuration[1];
            char temp4=obj.configuration[2];
            obj.configuration[13]=obj.configuration[5];
            obj.configuration[14]=obj.configuration[6];
            obj.configuration[1]=obj.configuration[9];
            obj.configuration[2]=obj.configuration[10];
            obj.configuration[5]=temp2;
            obj.configuration[6]=temp1;
            obj.configuration[9]=temp3;
            obj.configuration[10]=temp4;
            temp1=obj.configuration[16];
            temp2=obj.configuration[17];
            obj.configuration[16]=obj.configuration[18];
            obj.configuration[17]=obj.configuration[19];
            obj.configuration[18]=temp1;
            obj.configuration[19]=temp2;
            break;
        }

        case 9: {

            //congiuration for L move
            temp1=obj.configuration[15];
            temp2=obj.configuration[12];
            obj.configuration[15]=obj.configuration[11];
            obj.configuration[12]=obj.configuration[8];
            obj.configuration[11]=obj.configuration[7];
            obj.configuration[8]=obj.configuration[4];
            obj.configuration[7]=obj.configuration[3];
            obj.configuration[4]=obj.configuration[0];
            obj.configuration[3]=temp1;
            obj.configuration[0]=temp2;
            temp1=obj.configuration[20];
            obj.configuration[20]=obj.configuration[23];
            obj.configuration[23]=obj.configuration[22];
            obj.configuration[22]=obj.configuration[21];
            obj.configuration[21]=temp1;
            break;
        }
        case 10:{

            //congiuration for Li move
            temp1=obj.configuration[15];
            temp2=obj.configuration[12];
            obj.configuration[15]=obj.configuration[3];
            obj.configuration[12]=obj.configuration[0];
            obj.configuration[3]=obj.configuration[7];
            obj.configuration[0]=obj.configuration[4];
            obj.configuration[7]=obj.configuration[11];
            obj.configuration[4]=obj.configuration[8];
            obj.configuration[11]=temp1;
            obj.configuration[8]=temp2;
            temp1=obj.configuration[20];
            obj.configuration[20]=obj.configuration[21];
            obj.configuration[21]=obj.configuration[22];
            obj.configuration[22]=obj.configuration[23];
            obj.configuration[23]=temp1;
            break;
        }
        case 11:{

            //congiuration for L2 move
            temp1=obj.configuration[15];
            temp2=obj.configuration[12];
            char temp3=obj.configuration[0];
            char temp4=obj.configuration[3];
            obj.configuration[15]=obj.configuration[7];
            obj.configuration[12]=obj.configuration[4];
            obj.configuration[0]=obj.configuration[8];
            obj.configuration[3]=obj.configuration[11];
            obj.configuration[7]=temp1;
            obj.configuration[4]=temp2;
            obj.configuration[8]=temp3;
            obj.configuration[11]=temp4;
            temp1=obj.configuration[20];
            temp2=obj.configuration[21];
            obj.configuration[20]=obj.configuration[22];
            obj.configuration[21]=obj.configuration[23];
            obj.configuration[22]=temp1;
            obj.configuration[23]=temp2;
            break;
        }
        case 12:{

            //congiuration for F move
            temp1=obj.configuration[8];
            temp2=obj.configuration[9];
            obj.configuration[8]=obj.configuration[18];
            obj.configuration[9]=obj.configuration[19];
            obj.configuration[18]=obj.configuration[2];
            obj.configuration[19]=obj.configuration[3];
            obj.configuration[2]=obj.configuration[22];
            obj.configuration[3]=obj.configuration[23];
            obj.configuration[22]=temp1;
            obj.configuration[23]=temp2;
            temp1=obj.configuration[4];
            obj.configuration[4]=obj.configuration[7];
            obj.configuration[7]=obj.configuration[6];
            obj.configuration[6]=obj.configuration[5];
            obj.configuration[5]=temp1;
            break;
        }
        case 13:{

            //congiuration for Fi move
            temp1=obj.configuration[8];
            temp2=obj.configuration[9];
            obj.configuration[8]=obj.configuration[22];
            obj.configuration[9]=obj.configuration[23];
            obj.configuration[22]=obj.configuration[2];
            obj.configuration[23]=obj.configuration[3];
            obj.configuration[2]=obj.configuration[18];
            obj.configuration[3]=obj.configuration[19];
            obj.configuration[18]=temp1;
            obj.configuration[19]=temp2;
            temp1=obj.configuration[4];
            obj.configuration[4]=obj.configuration[5];
            obj.configuration[5]=obj.configuration[6];
            obj.configuration[6]=obj.configuration[7];
            obj.configuration[7]=temp1;
            break;
        }
        case 14:{

            //congiuration for F2 move
            temp1=obj.configuration[8];
            temp2=obj.configuration[9];
            char temp3=obj.configuration[22];
            char temp4=obj.configuration[23];
            obj.configuration[8]=obj.configuration[2];
            obj.configuration[9]=obj.configuration[3];
            obj.configuration[22]=obj.configuration[18];
            obj.configuration[23]=obj.configuration[19];
            obj.configuration[2]=temp1;
            obj.configuration[3]=temp2;
            obj.configuration[18]=temp3;
            obj.configuration[19]=temp4;
            temp1=obj.configuration[4];
            temp2=obj.configuration[5];
            obj.configuration[4]=obj.configuration[6];
            obj.configuration[5]=obj.configuration[7];
            obj.configuration[6]=temp1;
            obj.configuration[7]=temp2;
            break;
        }
        case 15:{

            //congiuration for B move
            temp1=obj.configuration[11];
            temp2=obj.configuration[10];
            obj.configuration[11]=obj.configuration[21];
            obj.configuration[10]=obj.configuration[20];
            obj.configuration[20]=obj.configuration[0];
            obj.configuration[21]=obj.configuration[1];
            obj.configuration[1]=obj.configuration[17];
            obj.configuration[0]=obj.configuration[16];
            obj.configuration[16]=temp2;
            obj.configuration[17]=temp1;
            temp1=obj.configuration[15];
            obj.configuration[15]=obj.configuration[14];
            obj.configuration[14]=obj.configuration[13];
            obj.configuration[13]=obj.configuration[12];
            obj.configuration[12]=temp1;
            break;
        }
        case 16:{

            //congiuration for Bi move
            temp1=obj.configuration[11];
            temp2=obj.configuration[10];
            obj.configuration[11]=obj.configuration[17];
            obj.configuration[10]=obj.configuration[16];
            obj.configuration[17]=obj.configuration[1];
            obj.configuration[16]=obj.configuration[0];
            obj.configuration[0]=obj.configuration[20];
            obj.configuration[1]=obj.configuration[21];
            obj.configuration[20]=temp2;
            obj.configuration[21]=temp1;
            temp1=obj.configuration[15];
            obj.configuration[15]=obj.configuration[12];
            obj.configuration[12]=obj.configuration[13];
            obj.configuration[13]=obj.configuration[14];
            obj.configuration[14]=temp1;
            break;
        }
        case 17:{

            //congiuration for B2 move
            temp1=obj.configuration[11];
            temp2=obj.configuration[10];
            char temp3=obj.configuration[16];
            char temp4=obj.configuration[17];
            obj.configuration[11]=obj.configuration[1];
            obj.configuration[10]=obj.configuration[0];
            obj.configuration[16]=obj.configuration[20];
            obj.configuration[17]=obj.configuration[21];
            obj.configuration[1]=temp1;
            obj.configuration[0]=temp2;
            obj.configuration[21]=temp4;
            obj.configuration[20]=temp3;
            temp1=obj.configuration[12];
            temp2=obj.configuration[13];
            obj.configuration[12]=obj.configuration[14];
            obj.configuration[13]=obj.configuration[15];
            obj.configuration[14]=temp1;
            obj.configuration[15]=temp2;
            break;
        }
    }
    return obj;
}


/*
 * This function generate unique code associated with
 * each state to avoid loops and free cube from
 * problem of rotation
 */
unsigned long long code_generator(CubeState obj){

    int temp[6];

    //Generate code for all cube
    for(int i= 0 ; i<6; i++){
        temp[i]=0;
        int t=0;

        //Generate code for each face which is unique
        for (int j=i*4; j<((i*4)+4); j++){
            switch(obj.configuration[j]){
                case('Y'):
                    t=0;
                    break;
                case('G'):
                    t=1;
                    break;
                case('W'):
                    t=5;
                    break;
                case('B'):
                    t=21;
                    break;
                case('O'):
                    t=85;
                    break;
                case('R'):
                    t=341;
                    break;
            }
            temp[i]=temp[i]+t;
        }
    }

    // sort code for all face
    sort(temp,temp+6);

    //concatenate code for all faces
    unsigned long long code=0;
    for (int i=0; i<6; i++){
        if(i<4)
            code=code*(1000);
        if(i>3)
            code=code*(10000);
        code=code+temp[i];
    }
    return code;
}


/*
 * This function check whether given state of cube is
 * solved or not
 */
bool check(CubeState *obj){

    //check each face
    for(int i=0; i<6; i++){
        int k=i*4;
        char temp=obj->configuration[k];

        //check each for color on each face

        for(int j=1; j<4; j++){
            if(obj->configuration[k+j]!=temp)
                return false;
        }
    }
    return true;
}

/*
 * This function give the sequence of moves
 * which have to be used to get solved state
 */
void give_solution(CubeState obj){

    //check if no move is used
    if(!obj.parent.size()){
        cout<<"Cube already in solved state \n";
        return;
    }

    //Display moves
    for(int i=0;i<obj.parent.size();i++)
        cout<<moves[obj.parent.at(i)]<<" ";
    cout<<endl;

}

/*
 * This function gets input from user in 2ways-:
 * 1. Sequence of scramble used to get to that state
 * 2. Color sequence of Cube
 *
 * "RFiRFiURU2F2RiUiR" This scramble yields a 10 move solution
 * "FRUiRiUiRURiFiRURiUiRiFRFi" This scramble has a 11 move solution
 */

int scramble(CubeState &one){
    int range[6]={4, 4, 4, 4, 4, 4};
    string sequence;
    int ch;

    cout<<"Enter Your choice \n 1 for entering scramble sequence \n";
    cout<<"2 for entering color schema\n";
    cin>>ch;
    if(ch==2){
        cout<<"Enter 24 color characters\n";
        cin>>sequence;
check_colors:
		
        if(sequence.length()!=24){
            cout<<"Wrong Sequence (Exactly 24 characters needed)\n";
            return -1;
        }
        bool sym;
        for(int i=0;i<24;i++){
            sym=true;
            for(int j=0;j<6;j++){
                if(color[j]==sequence[i]){
                    sym=false;
                    if(range[j]>0){
                        range[j]--;
                        j=7;
                        one.configuration[i]=sequence[i];
                    }
                    else{
                        cout<<"Wrong Sequence (No color shal";
                        cout<<"be present more than 4 times)\n";
                       return -1;
                    }
                }
            }
            if(sym){
                cout<<"Wrong Sequence";
                cout<<"(Only standard colors are needed)\n";
               return -1;
            }
        }
        cout<<"Wonderfull\n";
        return 0;
    }
    cout<<"Enter the scramble sequence\n";
    cin>>sequence;
check_scramble:
    string x; //temporary
    int wrong=1;
    for(int i=0;i<sequence.length();i++){
        x="";
        x=sequence[i];
        if(sequence[i+1]=='i'||sequence[i+1]=='2'){
            x=x+sequence[i+1];
            i++;
        }
        for(int j=0;j<18;j++){
            if(x==moves[j]){
                one=generate_new(one, j);
                wrong=0;
                break;
            }
        }
        if(wrong==1){
            cout<<"wrong scramble \n";
           return -1;
         }
    }

    return 0;
}


