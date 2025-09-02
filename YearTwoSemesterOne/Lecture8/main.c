#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>

void main() {
	int i, numberOfNewProduct, productID, stock, reorderThreshold;
	char productName[30], deptName[30];
	float price;
	FILE* op;

	printf("Plase enter the number of new products: ");
	scanf_s("%d", &numberOfNewProduct);

	for (int i = 0; i < numberOfNewProduct; i++) {
		printf("Please enter the product name: ");
		scanf_s("%s", productName);
	}

}