/*********************************************
 * CO322: Data structures and algorithms Implementation of the hashTable
 *********************************************/
class HashTableImp implements HashTable {

	/* Put your code here */
	public static class Hash_node {
		String key;
		int value = 0;
		Hash_node next;
	}

	public Hash_node[] table; // hash table
	private int count;

	public HashTableImp(int initialSize) {
		if (initialSize <= 0) {
			System.out.println("Please enter a positive number");
			return;
		}
		table = new Hash_node[initialSize];
	}
	/* *************************************************************************** */
	// Uncomment the below hash function one at a time

	// hashing function 1
	// public int hashing(String key) {
	// 	int hash = 0;
	// 	for (int i = key.length() - 1; i >= 0; i--) {
	// 		hash = (hash + (key.charAt(i) * (int) (Math.pow(128, i)))) % table.length;
	// 	}
	// 	return (hash % table.length);
	// }

	// hasing function 2
	public int hashing(String key) {
		int hash = 0;
		for (int i = 0; i < key.length(); i++) {
			hash = (31 * hash + key.charAt(i)) % table.length;
		}
		return (hash % table.length);
	}
	
	/* *************************************************************************** */

	public void insert(String key) {

		int bucket = hashing(key); // get the bucket number by hash code
		Hash_node list = null;

		list = table[bucket]; // For traversing the linked list

		// check whether the key is included in the list
		while (list != null) {
			if (list.key.equals(key)) {
				break;
			}
			list = list.next;
		}

		// the key exists
		if (list != null) {
			// value needs to be updated
			list.value = list.value + 1;
		} else {
			//new node containing the key is added if the key is not found
			Hash_node newNode = new Hash_node();
			newNode.key = key;
			newNode.value = newNode.value + 1;
			newNode.next = table[bucket];
			table[bucket] = newNode;
			count++;
		}
	}

	// search the given key
	public int search(String key) {
		int bucket = hashing(key);
		Hash_node list = table[bucket];

		while (list != null) {
			if (list.key.equals(key)) {
				return list.value;
			}
			list = list.next;
		}
		// if the key does not exist return 0
		return 0; 
	}

	// returns the number of nodes in a bucket
	public void findBucketSize(int length) {
		int x_squared = 0;
		int sum = 0;
		for (int i = 0; i < length; i++) {
			int counter = 0;
			Hash_node list = table[i];

			while (list != null) {
				list = list.next;
				counter++;
			}

			sum = sum + counter;
			x_squared = x_squared + (int) Math.pow(counter, 2);
			System.out.println("Nodes In Bucket " + i + " : " + counter);
		}
		float avg = (float) (sum / (float) length);
		float var = (float) (x_squared / length) - (float) (Math.pow(avg, 2));
		System.out.println("Total : " + sum);
		System.out.println("Avg : " + avg);
		System.out.println("Deviation : " + Math.sqrt(var));
	}

}