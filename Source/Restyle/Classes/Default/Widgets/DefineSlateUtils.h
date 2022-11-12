// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#ifndef	SLATE_CONSTRUCT_IMP
#define SLATE_CONSTRUCT_IMP(...) \
	PreConstruct(__VA_ARGS__); \
	InConstruct(__VA_ARGS__); \
	PostConstruct(__VA_ARGS__);
#endif

#ifndef SLATE_CONSTRUCT
#define SLATE_CONSTRUCT(Implementation, ...) \
protected:\
void PreConstruct(__VA_ARGS__);\
void InConstruct(__VA_ARGS__);\
void PostConstruct(__VA_ARGS__);\
\
public:\
void Construct(__VA_ARGS__) {Implementation}
#endif
