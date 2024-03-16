// Задание: Управление массивом структур
// Вариант 6

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date  {
	int day;
	int month;
	int year;
};

typedef struct date Date;

struct reader {
	char FIO[80];
	int ticket;
	char bookName[100];
	Date returnDate;
};

typedef struct reader Reader;

void PrintMenu();
int CheckDate(Date* dPtr);
int IsEmpty(Reader* rPtr);
void PrintEmptyReaders(Reader* rPtr, int n);
void PrintElement(const Reader* rPtr);
void PrintReaders(const Reader* rPtr, int amount);
void InsertReaders(Reader* rPtr, int n);
void InputReader(Reader* rPtr, int i);
void ClearReader(Reader* rPtr, int n);
int FindMinTicket(Reader* rPtr, int n, int startPosition);
void SortReaders(Reader* rPtr, int n);
void FindReader(Reader* rPtr, int n);
Reader* DeleteReader(Reader* rPtr, int* n);
void EditReader(Reader* rPtr, int n);
void FindPopularBook(Reader* rPtr, int n);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n;
	printf("Введите количество читателей: ");
	scanf("%d", &n);

	Reader* readersPtr = (Reader*)calloc(n, sizeof(Reader));

	int isRunning = 1;
	
	while (isRunning) {
		system("cls");
		PrintMenu();
		int choice;
		scanf("%d", &choice);
		getchar();

		switch (choice) {
		case 1:
			ClearReader(readersPtr, n);
			break;
		case 2:
			PrintEmptyReaders(readersPtr, n);
			break;
		case 3:			
			InsertReaders(readersPtr, n);					
			break;
		case 4:
			PrintReaders(readersPtr, n);
			break;
		case 5: 
			printf("\n***Данные читателя с минимальным значением билета***\n\n");
			if (FindMinTicket(readersPtr, n, 0) >= 0) {
				printf("Читатель %d\n", FindMinTicket(readersPtr, n, 0) + 1);
				PrintElement(&readersPtr[FindMinTicket(readersPtr, n, 0)]);
				getchar();
			}
			else {
				printf("Нет данных! Поиск наименьшего невозможен!\n");
				getchar();
			}
			break;
		case 6:
			SortReaders(readersPtr, n);
			break;
		case 7:
			FindReader(readersPtr, n);
			break;
		case 8:
			readersPtr = DeleteReader(readersPtr, &n);
			break;
		case 9:
			EditReader(readersPtr, n);
			break;
		case 10:
			FindPopularBook(readersPtr, n);
			break;
		case 0:
			isRunning = 0;
			break;
		default:
			printf("Неверный пункт меню! Нажмите Enter и попробуйте еще раз!\n");
			getchar();
			break;
		}
		
	}
	free(readersPtr);
	printf("Программа завершена!!!\n");
	return 0;

}

void PrintMenu() {
	printf("Меню:\n");
	printf("[1] Очистка читательского билета\n");//
	printf("[2] Поиск свободного(пустого) читательского билета\n");//
	printf("[3] Ввод читателей с клавиатуры\n");//
	printf("[4] Вывод читателей на экран\n");//
	printf("[5] Поиск читателя c минимальным номером читательского билета\n");//
	printf("[6] Сортировка читателей в порядке возрастания номера читательского билета\n");//
	printf("[7] Поиск в массиве структур читателя с заданным значением поля\n");//
	printf("[8] Удаление читателя\n");//
	printf("[9] Изменение (редактирование) данных читателя\n");
	printf("[10] Вычислить популярную книгу (наиболее часто повторяющуюся)\n");
	printf("[0] Выход из программы\n");
	printf("Введите пункт меню: ");
	char* FindString(char* text, char* key);
}

void ClearReader(Reader* rPtr, int n) {
	printf("\nВведите номер читателя для очистки данных (1 - %d): ", n);
	int id;
	scanf("%d", &id);
	while (id < 1 || id > n) {
		printf("Неверный id! Попробуйте еще раз: ");
		scanf("%d", &id);
	}
	printf("\nЧитатель %d.\n", id);
	PrintElement(&rPtr[id - 1]);
	if (!IsEmpty(&rPtr[id - 1])) {
		memset(&rPtr[id - 1], NULL, sizeof(Reader));
		printf("Данные о читателе %d удалены!\n", id);
	}
	else {
		printf("Данные о читателе %d уже пусты!\n", id);
	}
	getchar();
	getchar();
}

void PrintEmptyReaders(Reader* rPtr, int n) {
	int count = 0;
	printf("Номера пустых читателей: ");
	for (int i = 0; i < n; i++) {
		if (IsEmpty(&rPtr[i])) {
			printf("%d ", i + 1);
			count++;
		}
	}
	if (count == 0)
		printf("Нет пустых читательских билетов!\n");
	printf("\n");
	getchar();
}

void InsertReaders(Reader* rPtr, int n) {
	
	int count = 0;
	printf("\n");
	for (int i = 0; i < n; i++) {
		if (IsEmpty(&rPtr[i])) {
			InputReader(rPtr, i);
			count++;
		}				
	}
	if (count == 0)
		printf("Данные всех читателей уже внесены!\n");
	else
		printf("Данные всех читателей успешно внесены!\n");
	getchar();
}

void InputReader(Reader* rPtr, int i)
{
	printf("Читатель %d.\n", i + 1);
	printf("Введите ФИО читателя: ");
	char tempFIO[80];
	gets_s(tempFIO, 80);
	strcpy(rPtr[i].FIO, tempFIO);
	printf("Введите номер читательского билета: ");
	scanf("%d", &rPtr[i].ticket);
	printf("Введите название книги: ");
	getchar();
	char tempBook[100];
	gets_s(tempBook, 100);
	strcpy(rPtr[i].bookName, tempBook);	
	printf("Введите дату возврата в формате дд.мм.гггг: ");
	scanf("%d.%d.%d", &rPtr[i].returnDate.day, &rPtr[i].returnDate.month, &rPtr[i].returnDate.year);	

	while (!CheckDate(&rPtr->returnDate)) {
		printf("Некорректная дата!\n");
		printf("Введите дату возврата в формате дд.мм.гггг: ");
		scanf("%d.%d.%d", &rPtr[i].returnDate.day, &rPtr[i].returnDate.month, &rPtr[i].returnDate.year);
	}
	printf("\nДанные о читателе успешно внесены\n\n");
	getchar();
}

int CheckDate(Date* dPtr) {
	int isDateCorrect = 0;
	int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (dPtr->month > 0 && dPtr->month <= 12) {
		if (dPtr->year % 4 == 0) {
			if (dPtr->year % 100 == 0) {
				if (dPtr->year % 400 == 0) {
					month[1] = 29;
				}
			}
			else {
				month[1] = 29;
			}
		}
		if (dPtr->day > 0 && dPtr->day <= month[dPtr->month - 1]) {
			isDateCorrect = 1;
		}
	}
	return isDateCorrect;

}

int IsEmpty(Reader* rPtr) {
	int empty = 0;
	if (!strlen(rPtr->FIO))
		empty = 1;
	return empty;
}

void PrintElement(const Reader* rPtr) {
	if (IsEmpty(rPtr)) {
		printf("Нет данных\n");
	}
	else {
		printf("ФИО читателя: %s\n",rPtr->FIO);		
		printf("Номер читательского билета: %d\n", rPtr->ticket);		
		printf("Название книги: %s\n", rPtr->bookName);		
		printf("Дата возврата: %02d.%02d.%04d\n\n", 
			rPtr->returnDate.day, rPtr->returnDate.month, rPtr->returnDate.year);		
	}
}

void PrintReaders(const Reader* rPtr, int amount) {
	printf("\n***Список читателей***\n");
	int count = 0;
	for (int i = 0; i < amount; i++) {		
		printf("\nЧитатель %d.\n", i + 1);
		PrintElement(&rPtr[i]);
		count++;
	}
	if (count == 0)
		printf("Читателей в базе данных не найдено!");
	getchar();
}

int FindMinTicket(Reader* rPtr, int n, int startPosition) {
	
	while (IsEmpty(&rPtr[startPosition])) {
		startPosition++;
	}
	if (startPosition == n)
		return -1;

	int minIndex = startPosition;
	int minTicket = rPtr[minIndex].ticket;
	
	for (int i = startPosition; i < n; i++) {
		if (!IsEmpty(&rPtr[i])) {
			if (rPtr[i].ticket < minTicket) {
				minTicket = rPtr[i].ticket;
				minIndex = i;				
			}
		}		
	}	
	
	return minIndex;
}

void SortReaders(Reader* rPtr, int n) {
	int minIndex = 0;
	for (int i = 0; i < n - 1; i++) {
		minIndex = FindMinTicket(rPtr, n, i);
		if (minIndex >= 0 && !IsEmpty(&rPtr[i])) {
			Reader temp = rPtr[minIndex];
			rPtr[minIndex] = rPtr[i];
			rPtr[i] = temp;
		}		
	}
	printf("Отсортированные читатели: \n");
	PrintReaders(rPtr, n);
}

void FindReader(Reader* rPtr, int n) {
	int count = 0;
	printf("\n[1] Осуществить поиск по фамилии\n");
	printf("[2] Осуществить поиск по номеру читательского билета\n");
	printf("Введите номер операции: ");
	int search;
	scanf("%d", &search);

	while (search < 1 || search > 2) {
		printf("Неверный выбор! Попробуйте еще раз: ");
		scanf("%d", &search);
	}

	char keyStr[30];
	int key;
	switch (search) {
	case 1:
		printf("\nВведите фамилию читателя: ");
		scanf("%s", keyStr);
		printf("\n***Читатели с указанной фамилией***\n");
		for (int i = 0; i < n; i++) {
			if (FindString(rPtr[i].FIO, keyStr)) {
				printf("\nЧитатель %d.\n", i + 1);
				PrintElement(&rPtr[i]);
				count++;
			}
		}
		if (count == 0)
			printf("Читателей с такой фамилией не найдено!\n");
		getchar();
		break;
	case 2:
		printf("\nВведите номер читательского билета: ");
		scanf("%d", &key);
		printf("\n***Читатель с указанным читательским билетом***\n");
		for (int i = 0; i < n; i++) {
			if (rPtr[i].ticket == key) {
				printf("\nЧитатель %d.\n", i + 1);
				PrintElement(&rPtr[i]);
				count++;
			}
			if (count == 0)
				printf("Читателей с таким читательским билетом не найдено\n");
		}
		getchar();
	}
	getchar();
}

char* FindString(char* text, char* key) {
	int i;
	for (; *text != '\0'; text++) {
		for (i = 0; text[i] == key[i] && text[i] != '\0'; i++);
		if (key[i] == '\0')
			return text;
	}
	return NULL;
}

Reader* DeleteReader(Reader* rPtr, int* n) {
	int id;
	printf("Введите id читателя для удаления (1 - %d): ", *n);
	scanf("%d", &id);
	while (id < 1 || id > *n) {
		printf("Неверный id! Попробуйте еще раз: ");
		scanf("%d", &id);
	}
	Reader* newReaders = (Reader*)calloc(*n - 1, sizeof(Reader));
	int j = 0;
	for (int i = 0; i < *n; i++) {
		if (&rPtr[i] != &rPtr[id - 1]) {
			newReaders[j] = rPtr[i];
			j++;
		}
	}
	printf("\nЧитатель %d.\n", id);
	PrintElement(&rPtr[id -1]);
	printf("Удален!!!\n");
	getchar();
	getchar();
	*n -= 1;
	free(rPtr);
	return newReaders;
}

void EditReader(Reader* rPtr, int n) {
	int id;
	printf("Введите id читателя для редактирования (1 - %d): ", n);
	scanf("%d", &id);
	while (id < 1 || id > n) {
		printf("Неверный id! Попробуйте еще раз: ");
		scanf("%d", &id);
	}

	printf("\nЧитатель %d до изменения данных.\n", id);
	PrintElement(&rPtr[id - 1]);

	printf("[1] Редактировать ФИО\n");
	printf("[2] Редактировать номер читательского билета\n");
	printf("[3] Редактировать название книги\n");
	printf("[4] Редактировать дату возврата\n");
	printf("[5] Редактировать все данные читателя\n");
	printf("Введите номер операции: ");
	int search;
	scanf("%d", &search);
	while (search < 1 || search > 5) {
		printf("Неверный выбор! Попробуйте еще раз: ");
		scanf("%d", &search);
	}

	getchar();

	switch (search) {
	case 1:
		if (!IsEmpty(rPtr)) {
			printf("Введите ФИО читателя: ");
			char tempFIO[80];
			gets_s(tempFIO, 80);
			strcpy(rPtr[id - 1].FIO, tempFIO);
		}
		else {
			printf("Экземпляр пустой! Сначала заполните все данные!\n");
			InputReader(rPtr, id - 1);
		}		
		break;
	case 2:
		if (!IsEmpty(rPtr)) {
			printf("Введите номер читательского билета: ");
			scanf("%d", &rPtr[id - 1].ticket);
			getchar();
		}
		else {
			printf("Экземпляр пустой! Сначала заполните все данные!\n");
			InputReader(rPtr, id - 1);
		}		
		break;
	case 3:
		if (!IsEmpty(rPtr)) {
			printf("Введите название книги: ");
			//getchar();
			char tempBook[100];
			gets_s(tempBook, 100);
			strcpy(rPtr[id - 1].bookName, tempBook);
		}
		else {
			printf("Экземпляр пустой! Сначала заполните все данные!\n");
			InputReader(rPtr, id - 1);
		}		
		break;
	case 4:
		if (!IsEmpty(rPtr)) {
			printf("Введите дату возврата в формате дд.мм.гггг: ");
			scanf("%d.%d.%d", &rPtr[id - 1].returnDate.day, &rPtr[id - 1].returnDate.month, &rPtr[id - 1].returnDate.year);
			while (!CheckDate(&rPtr->returnDate)) {
				printf("Некорректная дата!\n");
				printf("Введите дату возврата в формате дд.мм.гггг: ");
				scanf("%d.%d.%d", &rPtr[id - 1].returnDate.day, &rPtr[id - 1].returnDate.month, &rPtr[id - 1].returnDate.year);
			}
			getchar();
		}
		else {
			printf("Экземпляр пустой! Сначала заполните все данные!\n");
			InputReader(rPtr, id - 1);
		}		
		break;
	case 5:
		InputReader(rPtr, id - 1);
		break;
	}
	
	printf("\nЧитатель %d после изменения данных.\n", id);
	PrintElement(&rPtr[id - 1]);
	
	getchar();

}

void FindPopularBook(Reader* rPtr, int n) {
	int maxCounter = 0;
	int counter = maxCounter;
	char popularBook[100];
	strcpy(popularBook, rPtr[0].bookName);

	for (int i = 0; i < n; i++) {
		counter = 0;
		for (int j = 0; j < n; j++) {
			if (strcmp(rPtr[i].bookName, rPtr[j].bookName) == 0) {
				counter++;
			}
		}
		if (counter > maxCounter) {
			maxCounter = counter;
			strcpy(popularBook, rPtr[i].bookName);
		}
	}

	printf("Самая популярная книга: %s\n", popularBook);
	printf("Она повторяется %d раз\n", maxCounter);
	getchar();
}

