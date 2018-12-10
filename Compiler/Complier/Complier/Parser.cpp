#include "pch.h"

extern const char * s = nullptr;

double ParseAndSolveEquation(const char * input_string)
{
    s = input_string;
    return GetG();
}

double GetG()
{
    const char * start_pos = s;
    GetSpace();
    double val = GetE();
    GetSpace();
    if (*s != '\0') {
        LOG_ERR_MESSAGE("no ending of string like \\0");
        exit(-1);
    }
    if (s == start_pos) {
        LOG_ERR_MESSAGE("0 length of formula");
        exit(-1);
    }
    return val;
}

double GetN()
{
    double val = 0.0;
    GetSpace();
    if (*s < '0' || *s > '9') {
        LOG_ERR_MESSAGE("you must specify number here");
        exit(-1);
    }
    else {
        val = val * 10 + *s - '0';
        s++;
    }
    while (('0' <= *s && *s <= '9')) {
        if (*s < '0' || *s > '9') {
            LOG_ERR_MESSAGE("you must specify number here");
            exit(-1);
        }
        val = val * 10 + *s - '0';
        s++;
    }
    if (*s == '.') {
        s++;
        int presicion = 0;
        double val2 = 0.0;
        while (('0' <= *s && *s <= '9')) {
            if (*s < '0' || *s > '9') {
                LOG_ERR_MESSAGE("you must specify number here");
                exit(-1);
            }
            presicion++;
            val2 = val2 * 10 + *s - '0';
            s++;
        }
        val = val + val2 / (pow(10, presicion));
    }
    GetSpace();
    return val;
}

double GetE()
{
    GetSpace();
    double val = GetT();
    GetSpace();
    while (*s == '+' || *s == '-') {
        char operand = *s;
        s++;
        GetSpace();
        double val2 = GetT();
        GetSpace();
        if (operand == '+') {
            val += val2;
        }
        else {
            val -= val2;
        }
    }
    return val;
}

double GetT()
{
    GetSpace();
    double val = GetP();
    GetSpace();
    while (*s == '*' || *s == '/') {
        char operand = *s;
        s++;
        GetSpace();
        double val2 = GetP();
        GetSpace();
        if (operand == '*') {
            val *= val2;
        }
        else {
            val /= val2;
        }
    }
    return val;
}

double GetP()
{
    GetSpace();
    if (*s == '(') {
        s++;
        GetSpace();
        double val = GetE();
        GetSpace();
        assert(*s == ')');
        s++;
        GetSpace();
        return val;
    }
    else if (*s >= '0' && *s <= '9') {
        GetSpace();
        double val = GetN();
        GetSpace();
        return val;
    }
    else {
        GetSpace();
        char * name = GetId();
        if (*s == '(') {
            double val = 0.0;
            s++;
            GetSpace();
            if (strcmp(name, "cos") == 0) {
                val = cos(GetE());
            }
            else if (strcmp(name, "sin") == 0) {
                val = sin(GetE());
            }
            else {
                LOG_ERR("function name isn't registered", name);
                exit(-1);
            }
            GetSpace();
            if (*s != ')') {
                LOG_ERR_MESSAGE("no ) after function");
                exit(-1);
            }
            s++;
            GetSpace();
            return val;
        }
        return 0; /// this is broken part must return name of id
    }
}

//double GetSin()
//{
//    GetSpace();
//    if (strcmp(GetId(), "sin")) {
//        if (*s == '(') {
//            s++;
//            GetSpace();
//            double val = sin(GetE());
//            GetSpace();
//            if (*s != ')') {
//                LOG_ERR_MESSAGE("no ) after function");
//                exit(-1);
//            }
//            s++;
//            return val;
//        }
//        else {
//            LOG_ERR_MESSAGE("{sin} is registered world, you can't use it as variable");
//            exit(-1);
//        }
//    }
//    return 0.0;
//}

//double GetCos()
//{
//    GetSpace();
//    if (strcmp(GetId(), "cos")) {
//        if (*s == '(') {
//            s++;
//            GetSpace();
//            double val = cos(GetE());
//            GetSpace();
//            if (*s != ')') {
//                LOG_ERR_MESSAGE("no ) after function");
//                exit(-1);
//            }
//            s++;
//            return val;
//        }
//        else {
//            LOG_ERR_MESSAGE("{cos} is registered world, you can't use it as variable");
//            exit(-1);
//        }
//    }
//    return 0.0;
//}

char * GetId()
{
    GetSpace();
    char * Id = (char*)calloc(MAX_NAME_LENGTH, sizeof(char));
    char * currentIdPosition = Id;
    if ((*s >= 'A' && *s <= 'Z') ||
        (*s >= 'a' && *s <= 'z') ||
        (*s == '_') ||
        (*s == '$'))
    {
        *currentIdPosition = *s;
        currentIdPosition++;
        s++;
    }
    while ((*s >= 'A' && *s <= 'Z') ||
        (*s >= 'a' && *s <= 'z') ||
        (*s >= '0' && *s <= '9') ||
        (*s == '_') ||
        (*s == '$'))
    {
        if (currentIdPosition - Id < MAX_NAME_LENGTH) {
            *currentIdPosition = *s;
            currentIdPosition++;
            s++;
        }
        else {
            *currentIdPosition = '\0';
            LOG_ERR_NUM("you can't use so long name here, max name lenght is", MAX_NAME_LENGTH);
            exit(-1);
        }
    }
    *currentIdPosition = '\0';
    GetSpace();
    return Id;
}

void GetSpace()
{
    while (*s == ' ') {
        s++;
    }
}
