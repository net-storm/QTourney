PARTICIPANT_PROPERTY(string       , status      , "Add", optional )
PARTICIPANT_PROPERTY(string       , name        , ""   , mandatory)
PARTICIPANT_PROPERTY(string       , team        , ""   , mandatory)
PARTICIPANT_PROPERTY(integer      , score       , 1600 , mandatory)
PARTICIPANT_PROPERTY(integer      , tours       , 0    , mandatory)
PARTICIPANT_PROPERTY(integer      , wins        , 0    , optional )
PARTICIPANT_PROPERTY(integer      , ties        , 0    , optional )
PARTICIPANT_PROPERTY(integer      , loses       , 0    , optional )
PARTICIPANT_PROPERTY(string       , first_name  , ""   , optional )
PARTICIPANT_PROPERTY(string       , middle_name , ""   , optional )
PARTICIPANT_PROPERTY(string       , last_name   , ""   , optional )
PARTICIPANT_PROPERTY(integer      , hits        , 0    , optional )
PARTICIPANT_PROPERTY(integer      , forfeits    , 0    , optional )
PARTICIPANT_PROPERTY(string       , the_rest    , ""   , optional ) // and so on

#undef PARTICIPANT_PROPERTY
