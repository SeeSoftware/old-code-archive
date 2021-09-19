#include "stdafx.h"
#include "Ackerman.h"


Ackerman::Ackerman()
{
}


Ackerman::~Ackerman()
{
}

long long Ackerman::ack (int m, int n) {

		long long ans;
		if (m == 0) {
			return n + 1;
		}
		else if (n == 0) {
			return ack(m - 1, 1);
		}
		else {
			return ack(m - 1, ack(m, n - 1));
		}
		return (ans);

	

}