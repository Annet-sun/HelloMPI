//1. Написать программу, печатающую номер процесса и общее количество процессов
//в коммуникаторе MPI_COMM_WORLD.
//#include <stdio.h> 
//#include "mpi.h"
//
//using namespace std;
//int main(int* argc, char** argv) {
//	int numtasks, rank;
//	MPI_Init(argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
//	printf("Hello MPI from process = %d, total number of processes: %d\n", rank, numtasks);
//	MPI_Finalize();
//}
//C:\MPI\HelloMPI\x64\Debug\HelloMPI.exe




////------------------------------------------------------Задание 2-------------------------------------------------------------------------------
//#include <stdio.h> 
//#include "mpi.h"
//#include <iostream>
//
////int MPI_Send(void* buf, int count, MPI_Datatype datatype, int dest,
////    int msgtag, MPI_Comm comm);
////buf - ссылка на адрес по которому лежат данные, которые мы пересылаем.В случае массивов ссылка на первый элемент.
////count - количество элементов в этом массиве, если отправляем просто переменную, то пишем 1.
////datatype - тут уже чутка посложнее, у MPI есть свои переопределенные типы данных которые существуют в С++
////dest - номер процесса кому отправляем сообщения.
////msgtag - ID сообщения(любое целое число)
////comm - Коммуникатор в котором находится процесс которому мы отправляем сообщение.
//
////int MPI_Recv(void* buf, int count, MPI_Datatype datatype, int source,
////    int tag, MPI_Comm comm, MPI_Status* status);
////buf - ссылка на адрес по которому будут сохранены передаваемые данные.
////count - максимальное количество принимаемых элементов.
////datatype - тип данных переопределенный в MPI(по аналогии с Send).
////source - номер процесса который отправил сообщение.
////tag - ID сообщения которое мы принимаем(любое целое число)
////comm - Коммуникатор в котором находится процесс от которого получаем сообщение.
////status - структура, определенная в MPI которая хранит информацию о пересылке и статус ее завершения.
//using namespace std;
//int main(int argc, char** argv) {
//    int rank;
//    int a[10];
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    int N = 100;
//    if (rank == 0) {
//        for (int i = 0; i < size(a); ++i) a[i] = rand() % N;
//        MPI_Send(a, size(a), MPI_INT, 1, 1, MPI_COMM_WORLD);
//    }
//    if (rank == 1) {
//        MPI_Recv(a, size(a), MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
//        for (int i = 0; i < size(a); i++) 
//            printf("%d ",a[i]);
//          
//    }
//    MPI_Finalize();
//}




//------------------------------------------------------Задание 3-------------------------------------------------------------------------------
//Используя блокирующую операцию передачи сообщений(MPI_Send и MPI_Recv),
//выполнить пересылку данных одномерного массива, из процесса с номером 1 на
//остальные процессы группы.На процессах получателях до выставления функции приема
//(MPI_Recv) определить количество принятых данных(MPI_Probe).Выделить память под
//размер приемного буфера, после чего вызвать функцию MPI_Recv.Полученное
//сообщение выдать на экран.
//
//#include <stdio.h> 
//#include "mpi.h"
//#include <iostream>
//
//using namespace std;
//int main(int argc, char** argv) {
//
//    int rank, size, count;
//    const int N = 10;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    if (rank == 1) {
//        int* arr = new int[N];
//        for (int i = 0; i < 10; ++i) arr[i] = rand() % 100;
//        //for (int i = 0; i < N; i++) arr[i] = i;
//        for (int i = 0; i < size; i++) {
//            if (i != 1) { MPI_Send(arr, N, MPI_INT, i, 0, MPI_COMM_WORLD); }
//        }
//    }
//    else {
//        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); //Получить данные о сообщении без его приема
//        MPI_Get_count(&status, MPI_INT, &count); //Получить количество данных по статусу
//        int* buf = new int[count];
//        MPI_Recv(buf, count, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
//        cout << "Process:" << rank << " || Count: " << count << " || Array: ";
//        for (int i = 0; i < 10; i++) {
//            printf("%d ", buf[i]);
//        }
//        cout << "\n";
//
//    }
//    MPI_Finalize();
//}


//------------------------------------------------------Задание 4-------------------------------------------------------------------------------
//Пусть векторы х, у заданы на нулевом процессе.Написать программу, в которой
//векторы равными блоками с нулевого процесса пересылаются остальным процессам.
//Пересылка данных осуществляется функцией MPI_Send.Все процессы по формуле
//вычисляют свои элементы искомых массивов.Каждый процесс отправляет на нулевой
//процесс посчитанные элементы массивов.В программе реализовать следующие операции
//вычисления векторов :
//a.z[i] = x[i] + y[i];
//b.z[i] = x[i] * y[i].
//
//#include <stdio.h> 
//#include "mpi.h"
//#include <iostream>
//
//using namespace std;
//int main(int argc, char** argv) {
//    int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    const int N = 20;
//    const int blockSize = int(N/5);
//    int localX [blockSize];
//    int localY [blockSize];
//    int localZA[blockSize];
//    int localZB[blockSize];
//    int x[N], y[N],za[N], zb[N];
//
//    if (rank == 0) {
//        for (int i = 0; i < N; ++i) {
//            x[i] = rand() % 10;
//            y[i] = rand() % 10;
//        }
//        printf("x : ");
//        for (int i = 0; i < N; ++i) {
//            printf("%d ", x[i]);
//        }
//        printf("\ny : ");
//        for (int i = 0; i < N; ++i) {
//            printf("%d ", y[i]);
//        }
//    }
//
//    MPI_Scatter(x, blockSize, MPI_INT, localX, blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//    MPI_Scatter(y, blockSize, MPI_INT, localY, blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//
//    for (int i = 0; i < blockSize; i++) {
//        // a. z[i] = x[i] + y[i]
//        localZA[i] = localX[i] + localY[i];
//        // b. z[i] = x[i] * y[i]
//        localZB[i] = localX[i] * localY[i];
//        }
//
//     MPI_Gather(localZA, blockSize, MPI_INT, za, blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//     MPI_Gather(localZB, blockSize, MPI_INT, zb, blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//    
//    if (rank == 0) {
//        printf("\na.z[i] = x[i] + y[i] : ");
//        for (int i = 0; i < N; ++i) printf("%d ", za[i]);
//
//        printf("\nb.z[i] = x[i] * y[i] : ");
//        for (int i = 0; i < N; ++i) printf("%d ", zb[i]);
//    }
//    MPI_Finalize();
//}


//#include <stdio.h> 
//#include "mpi.h"
//#include <iostream>
//
//using namespace std;
//int main(int argc, char** argv) {
//    int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    const int N = 28;
//    const int blockSize = int(N / 7);
//    if (rank == 0) {
//        int x[N], y[N], za[N], zb[N];
//        for (int i = 0; i < N; ++i) {
//            x[i] = rand() % 5;
//            y[i] = rand() % 5;
//        }
//        printf("x : ");
//        for (int i = 0; i < N; ++i) {
//            printf("%d ", x[i]);
//        }
//        printf("\ny : ");
//        for (int i = 0; i < N; ++i) {
//            printf("%d ", y[i]);
//        }
//
//        printf("\n");
//        for (int i = 1; i < size; i++) {
//            MPI_Send(&x[(i - 1) * blockSize], blockSize, MPI_INT, i, 0, MPI_COMM_WORLD);
//            MPI_Send(&y[(i - 1) * blockSize], blockSize, MPI_INT, i, 1, MPI_COMM_WORLD);
//        }
//
//        for (int i = 1; i < size; i++) {
//            MPI_Recv(&za[(i - 1) * blockSize], blockSize, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
//            MPI_Recv(&zb[(i - 1) * blockSize], blockSize, MPI_INT, i, 3, MPI_COMM_WORLD, &status);
//        }
//
//        printf("\na.z[i] = x[i] + y[i] : ");
//        for (int i = 0; i < N; ++i) printf("%d ", za[i]);
//
//        printf("\nb.z[i] = x[i] * y[i] : ");
//        for (int i = 0; i < N; ++i) printf("%d ", zb[i]);
//    }
//    else {
//        int localX[blockSize];
//        int localY[blockSize];
//        int localZA[blockSize];
//        int localZB[blockSize];
//        MPI_Recv(&localX, blockSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//        MPI_Recv(&localY, blockSize, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
//       
//        for (int i = 0; i < blockSize; i++) {
//            // a. z[i] = x[i] + y[i]
//            localZA[i] = localX[i] + localY[i];
//            // b. z[i] = x[i] * y[i]
//            localZB[i] = localX[i] * localY[i];
//
//        }
//        MPI_Send(&localZA, blockSize, MPI_INT, 0, 2, MPI_COMM_WORLD);
//        MPI_Send(&localZB, blockSize, MPI_INT, 0, 3, MPI_COMM_WORLD);
//    }
//    MPI_Finalize();
//}



//------------------------------------------------------Задание 5-------------------------------------------------------------------------------
//Пусть на нулевом процессе задана матрица А и вектор х.Написать программу, в
//которой матрица равными блоками с нулевого процесса пересылается остальным
//процессам.Пересылка данных осуществляется функцией MPI_Send.Все процессы по
//формуле вычисляют свои элементы искомых массивов.Каждый процесс отправляет на
//нулевой процесс посчитанные элементы массивов.В программе реализовать операцию x =
//diag(A) - выделения главной диагонали

//#include <stdio.h> 
//#include "mpi.h"
//#include <iostream>
//
//using namespace std;
//int main(int argc, char** argv){
//    int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    const int N = 14;
//    const int blockSize = int(N / (7));
//    if (rank == 0) {
//        int x [N];
//        int a [N][N];
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; ++j) {
//                a[i][j] = rand() % 5;
//                printf("%d ", a[i][j]);
//            }
//            printf("\n");
//        }
//        
//        printf("\n");
//        for (int i = 0; i < size - 1; i++) {
//            MPI_Send(a[i*blockSize], blockSize*N, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
//        }
//        for (int i = 0; i < size - 1; i++) {
//            MPI_Recv(&x[i*blockSize], blockSize, MPI_INT, i + 1, 2, MPI_COMM_WORLD, &status);
//        }
//
//        printf("\nx : ");
//        for (int i = 0; i < N; ++i) printf("%d ", x[i]);
//    }
//    else {
//
//        int locala [blockSize][N];
//        int* localx = new int[N];
//
//        MPI_Recv(&locala, N * blockSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//
//        int j = (rank - 1) * blockSize;
//        for (int i = 0; i < blockSize; i++) {
//            localx[i] = locala[i][j + i];
//        }
//        MPI_Send(localx, blockSize, MPI_INT, 0, 2, MPI_COMM_WORLD);
//    }
//    MPI_Finalize();
//}


//------------------------------------------------------Задание 6-------------------------------------------------------------------------------
//Разработать программу, в которой два процесса многократно обмениваются
//сообщениями длиной n байт.Выполнить эксперименты и оценить зависимость времени
//выполнения операции от длины сообщения.Рассмотреть два варианта обмена
//сообщениями
//a.PingPong - двунаправленная передача.Выполняется передача данных от одного
//процесса другому с последующим возвратом переданных данных в исходный процесс.
//Время выполнение замеряется после получения обратного ответа на исходном процессе.
//b.PingPing - однонаправленная передача.Два процесса одновременно выполняют
//передачу данных друг другу.Время выполнение замеряется после получения сообщения
//каждым процессом


 //                                                           n=2
//#include <stdio.h> 
//#include "mpi.h"
//#include <iostream>
//#include <random>
//
//int const n = 10;
//
//void ping_pong(int rank);
//void ping_ping(int rank);
//
//using namespace std;
//int main(int argc, char** argv) {
//    
//    int rank, size;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    //ping_pong(rank);
//    ping_ping(rank);
//
//    MPI_Finalize();
//}
//
//
//void ping_pong(int rank) {
//    static int* mess = new int[n];
//
//    if (rank == 0) {
//        std::random_device rd;
//        std::mt19937 gen(rd());
//        std::uniform_int_distribution<> dist(0, 100);
//
//        for (int i = 0; i < n; i++) {
//            mess[i] = dist(gen);
//        }
//
//        double start = MPI_Wtime();
//
//        MPI_Send(mess, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
//        MPI_Recv(mess, n, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//
//        double end = MPI_Wtime(); 
//        printf("\nProcess %d received a return response later %f \n", rank, end-start);
//    }
//    else {
//        int* received = new int[n];
//
//        MPI_Recv(received, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//        MPI_Send(received, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
//    }
//}
//
//
//void ping_ping(int rank) {
//    static int* mess = new int[n];
//    
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dist(0, 100);
//    
//    printf("\n Message from %i\n",rank);
//    for (int i = 0; i < n; i++) {
//        mess[i] = dist(gen);
//        printf("%d ",mess[i]);
//    }
//    
//    double start;
//    
//    MPI_Barrier(MPI_COMM_WORLD); //все процессы, участвующие в коммуникаторе,
//    //должны достигнуть этой точки в коде, прежде чем любой из них сможет продолжить выполнение.
//    
//    if (rank == 0) {
//        start = MPI_Wtime();
//        MPI_Send(mess, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
//    }
//    else {
//        start = MPI_Wtime();
//        MPI_Send(mess, n, MPI_INT, 0, 1, MPI_COMM_WORLD);
//    }
//    if (rank == 0) {
//        static int* received = new int[n];
//        MPI_Recv(received, n, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//    }
//    else {
//        static int* mess2 = new int[n];
//        MPI_Recv(mess2, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//    }
//    MPI_Barrier(MPI_COMM_WORLD);
//    
//    double end = MPI_Wtime();
//
//    printf("\nProcess %d received a return response later %f \n",rank, end-start);
//}


//------------------------------------------------------Задание 7-------------------------------------------------------------------------------
//Разработать программу, в которой два процесса многократно обмениваются
//Написать программу вычисления нормы ‖𝑥‖1 = ∑(𝑖 = 0:𝑛−1) |𝑥𝑖| 
//вектора x.Для распределения элементов вектора x по процессам использовать функцию MPI_Scatter.Для
//получения итоговой суммы на нулевом процессе использовать функцию MPI_Reduce соперацией MPI_Sum.

//#include <iostream>
//#include <mpi.h>
//#include <random>
//
//int const N = 16;
//
//void main(int argc, char** argv) {
//
//    int rank, size;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    int const block = 4; //4 процесса
//
//    int x[N], res[block];
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dist(1, 100);
//
//    if (rank == 0) {
//        printf("x: ");
//        for (int i = 0; i < N; i++) {
//            x[i] = dist(gen);
//            printf("%d ", x[i]);
//        }
//    }
//
//    MPI_Scatter(&x[0], block, MPI_INT, &res[0], block, MPI_INT, 0, MPI_COMM_WORLD);
//
//    int sum = 0;
//    for (int i = 0; i < block; ++i) {
//        sum += abs(res[i]);
//    }
//
//    int result;
//    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        printf("\nNorm of vector x = %d", result);
//    }
//    printf("\n");
//
//    finish: MPI_Finalize();
//}


//------------------------------------------------------Задание 8-------------------------------------------------------------------------------
//Написать программу вычисления скалярного произведения двух векторов.Для
//распределения элементов векторов x, у по процессам использовать функцию MPI_Scatter.
//Для получения итоговой суммы на нулевом процессе использовать функцию MPI_Reduce
//с операцией MPI_Sum.

//#include <iostream>
//#include <mpi.h>
//#include <random>
//
//int const N = 16;
//
//void main(int argc, char** argv) {
//
//    int rank, size;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    int const block = 4; //4 процесса
//
//    int x[N], xb[block], y[N], yb[block];
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dist(1, 10);
//
//    if (rank == 0) {
//        printf("x: ");
//        for (int i = 0; i < N; i++) {
//            x[i] = dist(gen);
//            printf("%d ", x[i]);
//        }
//        printf("\ny: ");
//        for (int i = 0; i < N; i++) {
//            y[i] = dist(gen);
//            printf("%d ", y[i]);
//        }
//    }
//
//    MPI_Scatter(&x[0], block, MPI_INT, &xb[0], block, MPI_INT, 0, MPI_COMM_WORLD);
//    MPI_Scatter(&y[0], block, MPI_INT, &yb[0], block, MPI_INT, 0, MPI_COMM_WORLD);
//
//    int sum = 0;
//    for (int i = 0; i < block; ++i) {
//        sum += xb[i]*yb[i];
//    }
//
//    int result;
//    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        printf("\nDot product of vector x and y = %d", result);
//    }
//    printf("\n");
//
//    finish: MPI_Finalize();
//}

//------------------------------------------------------Задание 9-------------------------------------------------------------------------------
//В массиве вещественных чисел вычислить минимальное значение и глобальный
//индекс минимального элемента.Использовать функции MPI_Scatter и MPI_Reduce с
//операцией MPI_MINLOC.

//#include <mpi.h>
//#include <iostream>
//#include <random>
//
//struct {
//    float value;
//    int index;
//} in, out;
//
//int const N = 16;
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    int const block = 4; //4 процесса
//    
//    float x[N], xb[block];
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<float> dist(0.0, 1.0);
//
//    if (rank == 0) {
//        printf("x: ");
//        for (int i = 0; i < N; i++) {
//            x[i] = dist(gen);
//            printf("%f ", x[i]);
//        }
//    }
//
//    MPI_Scatter(&x[0], block, MPI_FLOAT, &xb[0], block, MPI_FLOAT, 0, MPI_COMM_WORLD);
//
//    //локальный minloc
//    in.value = xb[0];
//    in.index = 0;
//    for (int i = 1; i < block; ++i) {
//        if (xb[i] < in.value) {
//            in.value = xb[i];
//            in.index = i;
//        }
//    }
//
//    //глобальный minloc 
//    in.index = rank * block + in.index;
//    int result;
//    MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        printf("\nMinimum = %f", out.value);
//        printf("\nMinimum index = %d", out.index);
//    }
//    printf("\n");
//
//    finish: MPI_Finalize();
//    return 0;
//}

//------------------------------------------------------Задание 10-------------------------------------------------------------------------------
//Написать программу умножения матрицы на вектор z = Ax.Распределить матрицу А
//равномерно вдоль строк, вектор х передать всем процессам.После выполнения операции
//умножения матрицы на вектор на каждом процессе необходимо выполнить сбор
//полученных локальный частей результирующего вектора на один из процессов.
//Использовать функцию MPI_Bcast для рассылки вектора x, для распределения элементов
//матрицы использовать функцию MPI_Scatter, для сбора локальных частей
//результирующего вектора в глобальный вектор использовать функцию MPI_Gather.


//#include <mpi.h>
//#include <iostream>
//#include <random>
//
//const int K = 4;
//const int N = 12;
//
//const int blockSize = 3;
//
//void main(int argc, char** argv) {
//
//    int rank, size;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    int x[K];
//
//    int ab[blockSize][K];
//    int zb[blockSize];
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dist(0, 10);
//
//    if (rank == 0) {
//        printf("x  = ");
//        for (int i = 0; i < K; ++i) {
//            x[i] = dist(gen);
//            printf("%d ", x[i]);
//        }
//
//
//        printf("\nA = \n");
//        int a[N][K];
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < K; ++j) {
//                a[i][j] = dist(gen);
//                printf("%d ", a[i][j]);
//            }
//            printf("\n");
//        }
//
//        MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);
//        MPI_Scatter(&(a[0][0]), blockSize * K, MPI_INT, &(ab[0][0]), blockSize * K, MPI_INT, 0, MPI_COMM_WORLD);
//    }
//    else {
//        MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);
//        int Z;
//        MPI_Scatter(&Z, blockSize * K, MPI_INT, &(ab[0][0]), blockSize * K, MPI_INT, 0, MPI_COMM_WORLD);
//    }
//    for (int i = 0; i < blockSize; ++i) {
//        zb[i] = 0;
//        for (int j = 0; j < K; ++j) {
//            zb[i] += ab[i][j] * x[j];
//        }
//    }
//
//    if (rank != 0) {
//        int Z;
//        MPI_Gather(&zb[0], blockSize, MPI_INT, &Z, blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//    }
//    else{
//        int Z[N];
//        MPI_Gather(&zb[0], blockSize, MPI_INT, &Z[0], blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//
//        printf("\n\nZ = ");
//        for (int i = 0; i < N; ++i) {
//            printf("%d ", Z[i]);
//        }
//    }
//
//    MPI_Finalize();
//}



//------------------------------------------------------Задание 11-------------------------------------------------------------------------------
//На процессе с номером 0 объявить и заполнить значениями матрицу a[8][8].
//Создать новый тип данных для рассылки нечетных строк матрицы а в матрицу b[4][8], и
//для рассылки четных строк матрицы в матрицу c[4][8], используя функцию
//MPI_Type_vector.

#include <mpi.h>
#include <iostream>
#include <random>
using namespace std;


const int N = 8;
const int blockRows = 4;

int main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int rows = 8;
    const int cols = 8;
    int a[N][N];
    int b[blockRows][N];
    int c[blockRows][N];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    if (rank == 0) {

        printf("\nA : \n");
        int a[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = dist(gen);
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        //Создание нового типа данных для рассылки нечетных/четных строк матрицы a
        MPI_Datatype newType;
        MPI_Type_vector(4, 8, 16, MPI_INT, &newType);
        MPI_Type_commit(&newType);

        MPI_Scatter(&a[1][0], 1, newType, &b[0][0], rows / 2 * cols, MPI_INT, 0, MPI_COMM_WORLD);//Рассылка нечетных строк матрицы a в матрицу b

        MPI_Scatter(&a[0][0], 1, newType, &c[0][0], rows / 2 * cols, MPI_INT, 0, MPI_COMM_WORLD);//Рассылка четных строк матрицы a в матрицу c

        MPI_Type_free(&newType);// Освобождение созданных типов данных
    }
    else {
        //Принимаем данные на других процессах
        MPI_Scatter(nullptr, 0, MPI_DATATYPE_NULL, &b[0][0], rows / 2 * cols, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(nullptr, 0, MPI_DATATYPE_NULL, &c[0][0], rows / 2 * cols, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        cout << "\nB : (odd lines)" << endl;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nC : (even lines)" << endl;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << c[i][j] << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
    return 0;
}