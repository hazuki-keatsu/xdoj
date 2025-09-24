#include <cstdio>
#include <string>

std::string toBinary_11(int n)
{
    std::string r;
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    if (11 - r.length() != 0)
    {
        int temp_len = 11 - r.length();
        for (int i = 0; i < temp_len; i++)
        {
            r = "0" + r;
        }
        return r;
    }
    return r;
}

std::string getS(std::string s)
{
    int g1[] = {s[10]-'0',s[8]-'0',s[6]-'0',s[4]-'0',s[2]-'0',s[0]-'0'};
    int g2[] = {s[9]-'0',s[8]-'0',s[5]-'0',s[4]-'0',s[1]-'0',s[0]-'0'};
    int g3[] = {s[7]-'0',s[6]-'0',s[5]-'0',s[4]-'0'};
    int g4[] = {s[3]-'0',s[2]-'0',s[1]-'0',s[0]-'0'};

    int init1 = 0;
    int init2 = 0;
    int init3 = 0;
    int init4 = 0;

    for (size_t i = 0; i < 6; ++i)
    {
        init1 ^= g1[i];
    }
    for (size_t i = 0; i < 6; ++i)
    {
        init2 ^= g2[i];
    }
    for (size_t i = 0; i < 4; ++i)
    {
        init3 ^= g3[i];
    }
    for (size_t i = 0; i < 4; ++i)
    {
        init4 ^= g4[i];
    }

    return std::to_string(init4) + std::to_string(init3) + std::to_string(init2) + std::to_string(init1);
}

void correct (std::string &s)
{
    if (std::stoi(getS(s)) == 0)
    {
        return;
    }

    for (int i = 0; i < 11; i++)
    {
        s[i] = (s[i] == '1' ? '0' : '1');
        if (std::stoi(getS(s)) == 0)
        {
            return;
        }
        s[i] = (s[i] == '1' ? '0' : '1');
    }
    
}

int main()
{
    int input;
    bool isRight = false;
    scanf("%d", &input);

    std::string bia = toBinary_11(input);

    correct(bia);

    std::string ss = std::string(1, bia[0]) + std::string(1, bia[1]) + std::string(1, bia[2]) + std::string(1, bia[4]) + std::string(1, bia[5]) + std::string(1, bia[6]) + std::string(1, bia[8]);
    printf("%s\n", ss.c_str());

    return 0;
}