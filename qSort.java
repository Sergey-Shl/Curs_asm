import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class qSort {
	public ArrayList<Integer> arr;
	public ArrayList<Integer> finalArr;
	public int size;
	
	class Thr extends Thread {
		private int left;
		private int right;
		
		Thr(int l, int r)
		{
			left = l;
			right = r;
		}
		
		@Override
	    public void run() {
			quickSort(left, right);
	    }
	}
	
	qSort(int s)
	{
		arr = new ArrayList<Integer>();
		finalArr = new ArrayList<Integer>();
		size = s;
		
		Random r = new Random();
		
		for(int i = 0; i < s; i++)
			arr.add(r.nextInt(1000));
	}
	
	public void quickSort(int l, int r)
	{
		//System.out.println(l + " " + r + "\n");
		int x = arr.get(l + (r - l) / 2);
		//запись эквивалентна (l+r)/2, 
		//но не вызввает переполнения на больших данных
		int i = l;
		int j = r;
		//код в while обычно выносят в процедуру particle
		while (i <= j)
		{
			while (arr.get(i) < x) i++;
			while (arr.get(j) > x) j--;
			if (i <= j)
			{
				Integer t = arr.get(j);
				arr.set(j, arr.get(i));
				arr.set(i, t);
				i++;
				j--;
			}
		}
		if (i<r)
			quickSort(i, r);

		if (l<j)
			quickSort(l, j);	
	}
	
	public void finalSortNew(int l, int r, int s)
	{
		int j = 0;
		int size = r - l + 1;
		int first_index = l;
		int second_index = l + size / 2;
		if (size % 2 != 0)
			second_index++;
		int start_second_index = second_index;
		if (s != -1)
		{
			second_index = s;
			start_second_index = s;
		}

		for (int i = first_index; i < first_index + size; i++, j++)
		{
			if (arr.get(first_index) < arr.get(second_index))
			{
				//finalArr.set(j, arr.get(first_index));
				finalArr.add(j, arr.get(first_index));
				//printf("\n%i", finalArr[j]);
				first_index++;
			} 
			else if (arr.get(second_index) < arr.get(first_index))
			{
				finalArr.add(j, arr.get(second_index));
				//printf("\n%i", finalArr[j]);
				second_index++;
			}
			else
			{
				finalArr.add(j, arr.get(first_index));
				//printf("\n%i", finalArr[j]);
				first_index++;
				j++;
				i++;
				finalArr.add(j, arr.get(second_index));
				//printf("\n%i", finalArr[j]);
				second_index++;
			}

			if (first_index >= start_second_index)
			{
				i++;
				j++;
				for (int k = i; j < size; k++, j++)
				{
					finalArr.add(k, arr.get(k));
					//printf("\n%i", finalArr[j]);
				}
				break;
			}

			if (second_index > r)
			{
				i++;
				j++;
				for (int k = first_index; j < size; k++, j++)
				{
					finalArr.add(j, arr.get(k));
					//printf("\n%i", finalArr[j]);
				}
				break;
			}
		}

		j = l;
		for (int i = 0; i < size; i++, j++)
		{
			arr.set(j, finalArr.get(i));
		}		
	}
	
	public void foo1(int n, int t)
	{
		int a = 2;
		int num_of_iter = 1;
		while (a < t)
		{
			a *= 2;
			num_of_iter++;
		}
		int num_of_elem = n; 
		int prev_num_of_parts = t; 
		int prev_size_of_part = num_of_elem / prev_num_of_parts;
		int num_of_parts = prev_num_of_parts / 2;
		int size_of_part = num_of_elem / num_of_parts;
		
		if (prev_num_of_parts % 2 != 0)
		{
			size_of_part = (num_of_elem - prev_size_of_part) / num_of_parts;
			num_of_parts++;
		}
		int counter = 0;
		int unprocessed_int = 0;
		boolean process_uproc = false;

		for (int i = 0; i < num_of_iter; i++)
		{
			for (int j = 0; j < num_of_parts; j++)
			{
				if (prev_num_of_parts % 2 != 0 && j == num_of_parts - 1)
				{
					unprocessed_int = num_of_elem - counter;
					process_uproc = true;
					break;
				}
				if (num_of_parts % 2 == 0 && unprocessed_int != 0 && j == num_of_parts - 1)
				{
					if (j * size_of_part == num_of_elem - unprocessed_int)
						break;
					finalSortNew(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
					unprocessed_int = 0;
					process_uproc = false;
					break;
				}
				if (num_of_parts == 1)
				{
					if (process_uproc)
					{
						finalSortNew(j * size_of_part, num_of_elem - 1, num_of_elem - unprocessed_int);
					}
					else
					{
						finalSortNew(j * size_of_part, num_of_elem - 1, -1);
						//printf("\n%i %i\n", j * size_of_part, num_of_elem - 1);
					}
					break;
				}
				if (i == num_of_iter - 1 && j == num_of_parts - 1)
				{
					finalSortNew(j * size_of_part, num_of_elem - 1, -1);
					//printf("\n%i %i\n", j * size_of_part, num_of_elem - 1);
					break;
				}
				finalSortNew(j * size_of_part, (j + 1) * size_of_part - 1, -1);
				//printf("\n%i %i\n", j * size_of_part, (j + 1) * size_of_part - 1);
				counter += size_of_part;
			}
			prev_num_of_parts = num_of_parts;
			prev_size_of_part = size_of_part;
			num_of_parts = prev_num_of_parts / 2;
			if (num_of_parts == 0)
				return;
			size_of_part = prev_size_of_part * 2;
			if (prev_num_of_parts % 2 != 0)
			{
				num_of_parts++;
			}
			counter = 0;
		}		
	}
	
	public void print()
	{
		for (int i = 0; i < size; i++)
			System.out.println(arr.get(i));
	}
	
	public void quickSortT(int n, int t)
	{
		System.out.println("Quick sort starts (" + t + " threads)");
		long start_time = System.currentTimeMillis();
		if (t > 1)
		{
			//ExecutorService service = Executors.newFixedThreadPool(t);
			
			int part_size = n / t;
			int add_proc = n % t;
			int prev_index = 0;
			int index = part_size;
			
			if (add_proc > 0)
			{
				index++;
				add_proc--;
			}
			
			for (long i = 0; i < t; i++)
			{
				if (i == t - 1)
				{
					System.out.println("Th" + i + " " + prev_index + " " + (n-1));
					Thr thread = new Thr(prev_index, n -1);
					thread.start();
					try {
						thread.join();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					//service.submit(new Thr(prev_index, n -1));
					break;
				}
				System.out.println("Th" + i + " " + prev_index + " " + (index-1));
				Thr thread = new Thr(prev_index, index - 1);
				thread.start();
				try {
					thread.join();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				//service.submit(new Thr(prev_index, index - 1));
				prev_index = index;
				index += part_size;
				if (add_proc > 0)
				{
					index++;
					add_proc--;
				}
			}
			
			foo1(size, t);
		}
		else
		{
			quickSort(0, n - 1);
		}
		
		System.out.println("Quick sort (" + t + " threads) time: " + (System.currentTimeMillis() - start_time));
		
	}
}
