//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using std::vector;
//using std::cin;
//using std::cout;
//
//class JobQueue {
//private:
//	//Số thread
//	int num_workers_;
//	//Danh sách các jobs cần xử lý
//	vector<int> jobs_;
//
//	//Các thread đã xử lý công việc theo thứ tự
//	vector<int> assigned_workers_;
//	//Thời gian bắt đầu của từng thread
//	vector<long long> start_times_;
//
//	void WriteResponse() const {
//		for (int i = 0; i < jobs_.size(); ++i) {
//			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
//		}
//	}
//
//	void ReadData() {
//		int m;
//		cin >> num_workers_ >> m;
//		jobs_.resize(m);
//		for (int i = 0; i < m; ++i)
//			cin >> jobs_[i];
//	}
//
//	void AssignJobs() {
//		// TODO: replace this code with a faster algorithm.
//
//		//Resize của danh sách các thread lần lượt được chạy bằng size của danh sách công việc
//		assigned_workers_.resize(jobs_.size());
//		//Danh sách thời gian bắt đầu có size bằng danh sách của công việc
//		start_times_.resize(jobs_.size());
//
//		//Tạo một vector có độ dài là num_workers (số thread) và giá trị đều là 0
//		vector<long long> next_free_time(num_workers_, 0);
//
//		//Duyệt qua các công việc cần xử lý
//		for (int i = 0; i < jobs_.size(); ++i) {
//			//
//			int duration = jobs_[i];
//			int next_worker = 0;
//			//Duyệt qua các thread sẵn có
//			for (int j = 0; j < num_workers_; ++j) {
//				//Nếu thời điểm thread j được giải phóng nhỏ hơn thread đang xét thì gán next_worker là j
//				if (next_free_time[j] < next_free_time[next_worker])
//					next_worker = j;
//			}
//			//Thread xử lý được gán cho next_worker
//			assigned_workers_[i] = next_worker;
//			//Thời gian bắt đầu được gán bằng next_free_time của next_worker
//			start_times_[i] = next_free_time[next_worker];
//			//next_free_time tại next_worker được tăng thêm thời gian là duration
//			next_free_time[next_worker] += duration;
//		}
//	}
//
//public:
//	void Solve() {
//		ReadData();
//		AssignJobs();
//		WriteResponse();
//	}
//};
//
//int main() {
//	std::ios_base::sync_with_stdio(false);
//	JobQueue job_queue;
//	job_queue.Solve();
//	return 0;
//}
