#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next; // create a next pointer (for linkedlist structure)
};

// Fill out this structure
struct HashType
{
    struct RecordType *record; // create a pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize; // hash function is x % tableSize
}

// parseData, printRecords and main remain unchanged


// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize); // call the hash function to get the index
    if (hashTable[index].record == NULL)
    {
        hashTable[index].record = record; // set 'record' equal to the HashType pointer in the table at index
    }
    else
    {
        struct RecordType *current = hashTable[index].record;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = record; // traverse to the end of the linkedlist and add 'record' to the end of it
    }
}

int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    for (int i = 0; i < tableSize; i++)
    {
        printf("Index %d -> ", i);
        struct RecordType *current = hashTable[i].record;
        while (current != NULL)
        {
            printf("%d, %c, %d -> ", current->id, current->name, current->order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    int hashTableSize = 8; // assign it a value, for example, 100
    struct HashType *hashTable = (struct HashType *)calloc(hashTableSize, sizeof(struct HashType)); // initialize a hashTable with calloc

    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    displayRecordsInHash(hashTable, hashTableSize);

    // free all the allocated memory
    free(hashTable);
    free(pRecords);

    return 0;
}
