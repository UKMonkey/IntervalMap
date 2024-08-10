#pragma once

#include <map>

template<typename K, typename V>
class interval_map {
	V m_valBegin;
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
		: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		if (!(keyBegin < keyEnd))
			return;

		// clear any entries in the range that we're about to assign.
		// Here is our O(log(n)) call.
		auto start = m_map.lower_bound(keyBegin);
		auto end = start;

		while (end != m_map.end())
		{
			if (keyEnd < (*end).first)
				break;
			++end;
		}

		// while we're here, we want to call the equivalent of (*this)[keyEnd]
		// since doing so would be a O(log(N)) operation we can't do that - but we've got the iterator
		// in question right here....
		auto upperBoundIt = end;
		if (upperBoundIt != m_map.end() && (*upperBoundIt).first < keyEnd )
			std::advance(upperBoundIt, 1);

		V lastItem(upperBoundIt == m_map.begin() ?
			m_valBegin : (--upperBoundIt)->second
		);

		start = m_map.erase(start, end);
		auto prestart = start;
		if (prestart != m_map.begin())
			--prestart;

		// now add the 2 entries we care about; one for the start range of this,
		// and one for the range after keyEnd.
		// If the item before is already our value, then we don't want to add it
		if ((start == m_map.begin() && !(val == m_valBegin))
			|| (!(prestart->second == val)))
			start = m_map.emplace_hint(start, std::make_pair(keyBegin, val));

		// If the last item is one that we've either just added, (or was already there),
		// then don't add it
		if (!(val == lastItem))
			m_map.emplace_hint(start, std::make_pair(keyEnd, std::move(lastItem)));
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}
};
