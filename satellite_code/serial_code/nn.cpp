

#include "macro.cpp"


string folder="../../data/";
string train_file="train_wkt_v4.csv";
//";
// For only serial code //////////
string grid_file="grid_sizes.csv";

ifstream read_write::train_fp((folder+train_file).c_str());                 // handle for input image file
ifstream read_write::grid_fp((folder+grid_file).c_str());                // handle for output image file
//float read_write::xmax=0,read_write::ymax=0;

uint32 read_write::train_x=IMAGE_X_SIZE,read_write::train_y=IMAGE_Y_SIZE;
uint32 read_write::train_max_x=P_IMAGE_X,read_write::train_max_y=P_IMAGE_Y;

 uint32 read_write::object_count=0;
 float read_write::A_x_fact=1,read_write::A_y_fact=1,read_write::P_x_fact=P_FACT,read_write::P_y_fact=P_FACT,read_write::M_x_fact=M_FACT,read_write::M_y_fact=4,read_write::RGB_x_fact=RGB_FACT,read_write::RGB_y_fact=RGB_FACT;
 string read_write::data_folder_path=folder;
 string read_write::file_name_of_image="NAN";
 TIFF* read_write::P_image;
 TIFF* read_write::A_image;
 TIFF* read_write::M_image;
 TIFF* read_write::RGB_image;



int main(int argc, char** argv) {
    int world_size;


    // Get the rank of the process

    int world_rank;
    srand (time(NULL));

    string *file_names=nullptr;
    uint16 no_of_file=file_selection(folder,grid_file,file_names);
    uint16 train_size=no_of_file*TRAINING_PERCENTAGE/100;
    uint16 test_size=no_of_file*TESTING_PERCENTAGE/100,temp=0,ram=0;
    string *train_file=new string[train_size];
    string *testing_file=new string[test_size];
    int i;

    for(i=0;i<train_size;i++)
    {
    //ram=rand();

        temp=rand()%(no_of_file-1)+0;
    train_file[i]=file_names[temp];

    }
    for(i=0;i<test_size;i++)
    {
    temp=rand()%(no_of_file-1)+0;
    testing_file[i]=file_names[temp];
    }
    //read_write **rw;
    //double ***temp_image;
    convolutional_network **p=new convolutional_network*[NO_CONVOLUTION_LAYERS];
    deconvolutional_network **dp=new deconvolutional_network*[NO_CONVOLUTION_LAYERS];
    int no_layer=10;
    char layer[]={'C','C','P','C','P','U','D','U','D','D'};
    uint16 im_size_x=RGB_IMAGE_X,im_size_y=RGB_IMAGE_Y;
    int j=0;
    for(i=0;i<no_layer;i++)
    {
        switch(layer[i])
        {
        case 'C':
            p[j]=new convolutional_network(im_size_x,im_size_y);
            dp[j]=new deconvolutional_network(im_size_x,im_size_y);
            j++;
            im_size_x-=WEIGHT_ROW;
            im_size_y-=WEIGHT_COLUMN;
        //    cout<<"in convo";
          // cout<<im_size_x<<"\t"<<im_size_y<<"\n";
            break;
           // continue;
         case 'P':
            im_size_x/=POOL_SIZE;
            im_size_y/=POOL_SIZE;
           // cout<<im_size_x<<"\t"<<im_size_y<<"\n";
       //     cout<<"In pool";
            break;
            //continue;
        }
    }
    serial_softmax_error *s=new serial_softmax_error(RGB_IMAGE_X,RGB_IMAGE_Y);
    read_write **rw;double ***temp_image;
    struct timeval  TimeValue_Start;
    struct timezone TimeZone_Start;
    struct timeval  TimeValue_Final;
    struct timezone TimeZone_Final;
    double time_overhead;
    long  time_start, time_end;

    serial_image_preprocessing(train_file[0],rw,temp_image);
    gettimeofday(&TimeValue_Start, &TimeZone_Start);
    neural_network_training(p,dp,s,no_layer,layer,temp_image[0],RGB_IMAGE_X,RGB_IMAGE_Y,rw[0]->train_array);
    //cout<<s->weight[0];
    //neural_network_training(p,dp,s,no_layer,layer,temp_image[1],RGB_IMAGE_X,RGB_IMAGE_Y,rw[1]->train_array);
    //cout<<s->weight[0];
    //neural_network_training(p,dp,s,no_layer,layer,temp_image[2],RGB_IMAGE_X,RGB_IMAGE_Y,rw[2]->train_array);
    //cout<<s->weight[0];
   // cout<<dp[2]->output[0][0][0];
   // neural_network_training(p,dp,s,no_layer,layer,temp_image[1],RGB_IMAGE_X,RGB_IMAGE_Y,rw[1]->train_array);
   double r= neural_network_testing(p,dp,s,no_layer,layer,temp_image[0],RGB_IMAGE_X,RGB_IMAGE_Y,rw[0]->train_array);
   gettimeofday(&TimeValue_Final, &TimeZone_Final);
   time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
   time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
   time_overhead = (time_end - time_start)/1000000.0;
   cout<<"Total time of training and testing";
   cout<<"\nTotal time for training by optimal parallel algorithom ="<<time_overhead;
    //cout<<dp[2]->weight[0][0];
   cout<<r;
    //neural_network_training(p,dp,s,no_layer,layer,);

}
