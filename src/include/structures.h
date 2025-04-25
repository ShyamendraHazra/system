#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {

} string;

typedef struct {
	string task_id;
	string title;
	string type;
	string rewards;
	uint8_t level;
	uint16_t required_exp;
} Tasks;

#endif // !STRUCTURES_H
