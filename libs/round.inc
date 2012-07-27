ROUND_PROPERTY(string       , status      , "Plan" , optional)
ROUND_PROPERTY(string       , name        , ""     , mandatory)
ROUND_PROPERTY(string       , seed        , "score", optional)
ROUND_PROPERTY(integer      , size        , 0      , optional)
ROUND_PROPERTY(deathmatch_t , deathmatch  , false  , optional)
ROUND_PROPERTY(string       , the_rest    , ""     , optional) // and so on

#undef ROUND_PROPERTY
