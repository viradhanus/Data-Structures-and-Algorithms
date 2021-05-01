import java.util.ArrayList;

class Fib {

	public static int fib_r(int x) {
		if (x <= 2)
			return 1;
		return fib_r(x - 1) + fib_r(x - 2);
	}

	public static int fib_i(int x) {
		int a = 1, b = 1, fib = 1, i = 2;
		while (i < x) {
			fib = a + b;
			a = b;
			b = fib;
			i += 1;
		}
		return fib;
	}

	public static void main(String[] args) {
		int problem_size = 40;		//problem size
		ArrayList<Long> runtime_rec = new ArrayList<Long>();  //holds runtimes corresponds to recusion implementation
		ArrayList<Long> runtime_iter = new ArrayList<Long>();  //holds runtimes corresponds to iteration implementation

		for (int x = 0; x < problem_size + 1; x++) {
			long startTime = System.nanoTime();	//get the starting time
			fib_i(x);
			long endTime = System.nanoTime();	//calculate the stopping moment time
			runtime_iter.add(endTime - startTime);	//add the time duration to the runtime_iter list
		}
		for (int i = 0; i < 41; i++) {
			System.out.println(i);
		}
		System.out.println("Runtimes for iterative implementation");
		for (long i : runtime_iter) {
			System.out.println(i);
		}

		for (int x = 0; x < problem_size + 1; x++) {
			long startTime = System.nanoTime();		//get the starting time
			fib_r(x);
			long endTime = System.nanoTime();		//calculate the stopping moment time
			runtime_rec.add(endTime - startTime);	//add the time duration to the runtime_rec list
		}
		System.out.println("Runtimes for recursive implementation");
		for (long i : runtime_rec) {
			System.out.println(i);
		}
	}
}
