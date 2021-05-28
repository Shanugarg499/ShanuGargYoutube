import java.util.*;

public class Code {
	
	public static int lowerBound(ArrayList<Integer> ar, int low, int high, int key) {
		while(low < high) {
			int mid = (low + high)/2;
			if(key == ar.get(mid))
				return mid;
			if(key > ar.get(mid)) {
				low = mid+1;
			}else {
				high = mid;
			}
		}
		return low;
	}
	
	public static int LISBF(int [] ar) {
		int n=ar.length;
		if(n <= 0)
			return 0;
		int res=1;
		for(int i=0; i<(1<<n); i++) {
			boolean firstTime=true;
			int curr=1;
			String bits=Integer.toBinaryString(i);
			int prev=-1;
			for(int j=0; j<bits.length() && j<ar.length; j++) {
				if(bits.charAt(j) == '1') {
					if(firstTime) {
						firstTime=false;
						prev=ar[j];
					}else {
						if(ar[j] <= prev)
							break;
						else {
							prev=ar[j];
							curr++;
						}
					}
				}
			}
			res = Math.max(curr, res);
		}
		return res;
	}
	
	public static int LISDP(int [] ar) {
		int n=ar.length;
		if(n <= 0)
			return 0;
		int res=1;
		int [] lisLengthUpto = new int [n];
		Arrays.fill(lisLengthUpto, 1);
		for(int i=1; i<n; i++) {
			int bestprefixLength=0;
			for(int j=0; j<i; j++) {
				if(ar[j] < ar[i]) {
					bestprefixLength = Math.max(bestprefixLength, lisLengthUpto[j]);
				}
			}
			lisLengthUpto[i] = Math.max(bestprefixLength+1, lisLengthUpto[i]);
			res = Math.max(res, lisLengthUpto[i]);
		}
		return res;
	}
	
	public static int LISUBLB(int [] ar) {
		int n=ar.length;
		if(n <= 0)
			return 0;
		int res=1;
		ArrayList<Integer> sortedlist = new ArrayList<Integer>();
		for(int i=0; i<n; i++) {
			if(sortedlist.isEmpty()) {
				sortedlist.add(ar[i]);
				continue;
			}
			if(ar[i] > sortedlist.get(sortedlist.size() - 1)) {
				sortedlist.add(ar[i]);
				res++;
			}else {
				if(sortedlist.get(lowerBound(sortedlist, 0, sortedlist.size() - 1, ar[i])) == ar[i])
					continue;
				sortedlist.set(lowerBound(sortedlist, 0, sortedlist.size() - 1, ar[i]), ar[i]);
			}
		}
		return res;
	}
	
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter length of array: ");
		int n=sc.nextInt();
		System.out.println("Enter elements of array: ");
		int [] ar=new int[n];
		for(int i=0; i<n; i++)
			ar[i] = sc.nextInt();
		System.out.println("LIS using Brute force: "+LISBF(ar));
		System.out.println("LIS using DP: "+LISDP(ar));
		System.out.println("LIS using UBLB: "+LISUBLB(ar));
	}
}