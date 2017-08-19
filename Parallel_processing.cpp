#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

struct a_job {
	long long next_free_time;
	long long index;
};

class JobQueue {
private:
	//Số thread
	long long num_workers_;
	//Danh sách các jobs cần xử lý
	vector<long long> jobs_;

	//Các thread đã xử lý công việc theo thứ tự
	vector<long long> assigned_workers_;
	//Thời gian bắt đầu của từng thread
	vector<long long> start_times_;
	
	//Số thread
	long long num_workers_1;
	//Danh sách các jobs cần xử lý
	vector<long long> jobs_1;

	//Các thread đã xử lý công việc theo thứ tự
	vector<long long> assigned_workers_1;
	//Thời gian bắt đầu của từng thread
	vector<long long> start_times_1;

	void WriteResponse() const {
		for (long long i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] /*<< "-----" << assigned_workers_1[i] << " " << start_times_1[i]*/ <<"\n";
		}



	}

	void ReadData() {
		long long m;
		cin >> num_workers_ >> m;
		// = num_workers_;
		jobs_.resize(m);
		//jobs_1.resize(m);
		for (long long i = 0; i < m; ++i)
			cin >> jobs_[i];

		/*for (long long i = 0; i < m; ++i)
			jobs_1[i] = jobs_[i];*/

	}


	//Hàm tính vị trí của parent
	long long Parent(long long i)
	{
		return i / 2;
	}

	//Tính vị trí của node bên trái
	long long Left(long long i)
	{
		return 2 * i;
	}

	//Tính vị trí node bên phải
	long long Right(long long i)
	{
		return 2 * i + 1;
	}

	//Hàm tìm node nhỏ nhất và đưa nó lên đỉnh, độ phức tạp logn
	void Min_Heapfy(long long i, vector<a_job> &next_free_time)
	{
		long long smallest = -1;
		long long l = Left(i);
		long long r = Right(i);

		//Nếu node left tồn tại
		if (l <= num_workers_)
		{
			//Nếu node bên trái nhỏ hơn node hiện tại
			if (next_free_time[l-1].next_free_time < next_free_time[i-1].next_free_time)
			{
				//Gán smallest là node bên trái
				smallest = l;
			}

			//Nếu 2 node bằng nhau
			else if (next_free_time[l - 1].next_free_time == next_free_time[i - 1].next_free_time)
			{
				//Nếu index node trái nhỏ hơn index hiện tại
				if (next_free_time[l - 1].index < next_free_time[i-1].index)
				{
					//Gán smallest là node bên trái
					smallest = l;
				}
				else
				{
					smallest = i;
				}
			}
			else
			{
				smallest = i;
			}
			
				
		}
		else smallest = i;
		if (r <= num_workers_ ){

			//Nếu node bên trái nhỏ hơn node hiện tại
			if (next_free_time[r - 1].next_free_time < next_free_time[smallest - 1].next_free_time)
			{
				//Gán smallest là node bên trái
				smallest = r;
			}

			//Nếu 2 node bằng nhau
			else if (next_free_time[r - 1].next_free_time == next_free_time[smallest - 1].next_free_time)
			{
				//Nếu index node trái nhỏ hơn index hiện tại
				if (next_free_time[r - 1].index < next_free_time[smallest-1].index)
				{
					//Gán smallest là node bên trái
					smallest = r;
				}
			}
	
		}


		//Neus i ko phải nhỏ nhất và nhỏ nhất đc tìm thấy
		//như vậy thứ tự sai tại node i
		if (i != smallest && smallest != -1)
		{
			swap(next_free_time[i - 1], next_free_time[smallest - 1]);
			//Kiểm tra tính đúng đắn tại node smallest
			Min_Heapfy(smallest, next_free_time);
		}
	}


	void AssignJobs() {
		// TODO: replace this code with a faster algorithm.
		//
		//Hướng cải tiến: Dùng heap để tìm next_free_time nhỏ nhất, 
		//mỗi lần next_free_time được gắn thì lại đẩy next_free_time nhỏ nhất khác lên
		//Độ phức tạp thuật toán dự kiến là nlogn
		//
		//Resize của danh sách các thread lần lượt được chạy bằng size của danh sách công việc
		assigned_workers_.resize(jobs_.size());
		//Danh sách thời gian bắt đầu có size bằng danh sách của công việc
		start_times_.resize(jobs_.size());
		
		//Tạo một vector có độ dài là num_workers (số thread) và giá trị đều là 0
		vector<a_job> next_free_time(num_workers_);
		for (long long i = 0; i < num_workers_; i++)
		{
			next_free_time[i].index = i;
			next_free_time[i].next_free_time = 0;
		}
		//Duyệt qua các công việc cần xử lý
		for (long long i = 0; i < jobs_.size(); ++i) {
			//Thời gian xử lý bằng giá trị của jobs_ tại i
			int duration = jobs_[i];
			//next_worker đặt mặc định là thread 0
			long long next_worker = next_free_time[0].index;
			//Thread xử lý được gán cho next_worker
			assigned_workers_[i] = next_worker;
			//Thời gian bắt đầu được gán bằng next_free_time của next_worker
			start_times_[i] = next_free_time[0].next_free_time;
			//next_free_time tại next_worker được tăng thêm thời gian là duration
			next_free_time[0].next_free_time += duration;
			Min_Heapfy(1, next_free_time);
		}
	}
	/*	//void AssignJobs1() {
		//	// TODO: replace this code with a faster algorithm.
	
		//	//Resize của danh sách các thread lần lượt được chạy bằng size của danh sách công việc
		//	assigned_workers_1.resize(jobs_1.size());
		//	//Danh sách thời gian bắt đầu có size bằng danh sách của công việc
		//	start_times_1.resize(jobs_1.size());
	
		//	//Tạo một vector có độ dài là num_workers (số thread) và giá trị đều là 0
		//	vector<long long> next_free_time(num_workers_1, 0);
	
		//	//Duyệt qua các công việc cần xử lý
		//	for (int i = 0; i < jobs_1.size(); ++i) {
		//		//
		//		int duration = jobs_1[i];
		//		int next_worker = 0;
		//		//Duyệt qua các thread sẵn có
		//		for (int j = 0; j < num_workers_1; ++j) {
		//			//Nếu thời điểm thread j được giải phóng nhỏ hơn thread đang xét thì gán next_worker là j
		//			if (next_free_time[j] < next_free_time[next_worker])
		//				next_worker = j;
		//		}
		//		//Thread xử lý được gán cho next_worker
		//		assigned_workers_1[i] = next_worker;
		//		//Thời gian bắt đầu được gán bằng next_free_time của next_worker
		//		start_times_1[i] = next_free_time[next_worker];
		//		//next_free_time tại next_worker được tăng thêm thời gian là duration
		//		next_free_time[next_worker] += duration;
		//	}
		//}*/
public:
	void Solve() {
		ReadData();
		AssignJobs();
	//	AssignJobs1();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}
