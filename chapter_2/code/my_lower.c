// lower: convert c to lower case; ASCII only
int lower(c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}
