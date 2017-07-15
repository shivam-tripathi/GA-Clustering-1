#include "chromosome.h"

Chromosome :: Chromosome(Data &_data) {
	this->data = &(_data);
	this->element_count = data->count;
	this->clusters_count = uniform_int(1, 11);
	for(int i=0; i<element_count; i++) {
		nodes.push_back(node(i, i));
	}
	this->populate();
}

void Chromosome :: populate() {
	std::vector<int> v;
	for(int i=0; i<element_count; i++) {
		v.push_back(i);
	}

	// printf("%d <==> %d\n", element_count, clusters_count);
	int cluster_size = element_count/clusters_count;
	printf("cluster_size max : %d\n", cluster_size);

	int size = element_count;
	for (int i=1; i<=clusters_count; i++) {

		cluster c;
		c.size = uniform_int(std::max(1, cluster_size-10), cluster_size);
		printf("\tCluster %d of size %d \n", i, c.size);

		std::vector<int> elements;
		if (i < clusters_count) {
			uniform_int(0, v.size()-1, c.size, elements);
			sort(elements.begin(), elements.end());
		}
		else {
			for(int i=0; i<v.size(); i++) {
				elements.push_back(i);
			}
		}

		c.begin = v[elements[0]];
		c.end = v[elements[elements.size()-1]];

		if (elements.size() > 1) {
			nodes[c.begin].r = v[elements[1]];
		}

		for(int i=1; i<elements.size()-1; i++) {
			int index = elements[i];
			int next_index = elements[i+1];
			int prev_index = elements[i-1];
			printf("\t\t%d\n", v[index]);
			nodes[v[index]].l = v[prev_index];
			nodes[v[index]].r = v[next_index];
			// add_cluster_intance(node.mean, v[index]);
		}

		std::cout << "\tCluster " << i << " of " << c.size << " completed " << std::endl;
		clusters.push_back(c);

		// Erase elements already used for referential integrity
		for(int i=0; i<elements.size(); i++) {
			assert(elements[i]-i < v.size());
			v.erase(v.begin() + elements[i] - i);
		}
	}
}

