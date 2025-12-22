#pragma once
#include <unordered_map>
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Опкоды инструкций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum OP_CODE {
	NOP,
	END,
	SLEEP,
	VAR,
	PRINT,
	FREE,
	LABEL,
	JUMP,
	INPT,
	CHANGE,
	TO,
	CALC,
	NEWTEMP,
	FORGET,
	TCOUNT,
	ISSET,
	TYPEOF,
	COMP,
	LOGIC,
	JIF,
	JIFNOT,
	DLABEL,
	SWAP,
	ARRAY,
	VTOARR,
	PUSHB,
	POPB,
	PUSHF,
	POPF,
	ERASE,
	INSRT,
	CLEAR,
	SIZEARR,
    SLICE,
    MERGE,
    SORT,
    UNIQUE,
    REVERSE,
    EQUAL,
    INNER,
    INALL,
    RINNER,
    RINALL,
    ARRTOMAP,
    INTERS,
    NOTINTERS,
    ARRTOSTR,
    SUM,
    AVG,
    MIN,
    MAX,
    RNGE,
    MEDIAN,
    MODE,
    STDDEV,
    PUSH,
    VTOMAP,
    GETVALS,
    GETKEYS,
    GETINTERF,
    KVINTERS,
    KVNOTINTERS,
    CLEARC,
    TOINTERF,
    UNINTERF,
    INTERFTOMAP,
    RAND,
    T,
    HRT,
    BETWEEN,
    JIFELSE,
    JSWITCH,
    FORMAT,
    TRIGON,
    DEGTORAD,
    RADTODEG,
    VARIANCE,
    CASTCHK,
    FINALIZE,
    CONST,
    ISCONST,
    INSTRUCT,
    E,
    PARSE,
    UNPARSE,
    PE,
    IF,
    FOR,
    BREAK,
    CONTINUE,
    WHILE,
    DOWHILE,
    SWITCH,
    ISCODE,
    SCONST,
    SFINALIZE,
    PLZDONTCRASH,
    PLZSHUTUP,
    TRY,
    THROW,
    PARALLEL,
    GETCHAR,
    SETCHAR,
    ARROW,
    CHEVRON,
    PLZTRUSTME,
    ICOUNT,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Таблица соответствий
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CTable {
    std::unordered_map<std::wstring, OP_CODE> opCodeMap = {
        {L"nop", OP_CODE::NOP},
        {L"end", OP_CODE::END},
        {L"sleep", OP_CODE::SLEEP},
        {L"var", OP_CODE::VAR},
        {L"print", OP_CODE::PRINT},
        {L"free", OP_CODE::FREE},
        {L"label", OP_CODE::LABEL},
        {L"jump", OP_CODE::JUMP},
        {L"input", OP_CODE::INPT},
        {L"change", OP_CODE::CHANGE},
        {L"to", OP_CODE::TO},
        {L"calc", OP_CODE::CALC},
        {L"newtemp", OP_CODE::NEWTEMP},
        {L"forget", OP_CODE::FORGET},
        {L"tcount", OP_CODE::TCOUNT},
        {L"isset", OP_CODE::ISSET},
        {L"typeof", OP_CODE::TYPEOF},
        {L"comp", OP_CODE::COMP},
        {L"logic", OP_CODE::LOGIC},
        {L"jif", OP_CODE::JIF},
        {L"jifnot", OP_CODE::JIFNOT},
        {L"dlabel", OP_CODE::DLABEL},
        {L"swap", OP_CODE::SWAP},
        {L"array", OP_CODE::ARRAY},
        {L"vtoarr", OP_CODE::VTOARR},
        {L"pushb", OP_CODE::PUSHB},
        {L"popb", OP_CODE::POPB},
        {L"pushf", OP_CODE::PUSHF},
        {L"popf", OP_CODE::POPF},
        {L"erase", OP_CODE::ERASE},
        {L"insert", OP_CODE::INSRT},
        {L"clear", OP_CODE::CLEAR},
        {L"size", OP_CODE::SIZEARR},
        {L"slice", OP_CODE::SLICE},
        {L"merge", OP_CODE::MERGE},
        {L"sort", OP_CODE::SORT},
        {L"unique", OP_CODE::UNIQUE},
        {L"reverse", OP_CODE::REVERSE},
        {L"equal", OP_CODE::EQUAL},
        {L"in", OP_CODE::INNER},
        {L"inall", OP_CODE::INALL},
        {L"rin", OP_CODE::RINNER},
        {L"rinall", OP_CODE::RINALL},
        {L"arrtomap", OP_CODE::ARRTOMAP},
        {L"inters", OP_CODE::INTERS},
        {L"notinters", OP_CODE::NOTINTERS},
        {L"arrtostr", OP_CODE::ARRTOSTR},
        {L"sum", OP_CODE::SUM},
        {L"avg", OP_CODE::AVG},
        {L"min", OP_CODE::MIN},
        {L"max", OP_CODE::MAX},
        {L"range", OP_CODE::RNGE},
        {L"median", OP_CODE::MEDIAN},
        {L"mode", OP_CODE::MODE},
        {L"stddev", OP_CODE::STDDEV},
        {L"push", OP_CODE::PUSH},
        {L"vtomap", OP_CODE::VTOMAP},
        {L"getvals", OP_CODE::GETVALS},
        {L"getkeys", OP_CODE::GETKEYS},
        {L"getinterf", OP_CODE::GETINTERF},
        {L"kvinters", OP_CODE::KVINTERS},
        {L"kvnotinters", OP_CODE::KVNOTINTERS},
        {L"clearc", OP_CODE::CLEARC},
        {L"tointerf", OP_CODE::TOINTERF},
        {L"uninterf", OP_CODE::UNINTERF},
        {L"interftomap", OP_CODE::INTERFTOMAP},
        {L"rand", OP_CODE::RAND},
        {L"t", OP_CODE::T},
        {L"hrt", OP_CODE::HRT},
        {L"between", OP_CODE::BETWEEN},
        {L"jifelse", OP_CODE::JIFELSE},
        {L"jswitch", OP_CODE::JSWITCH},
        {L"format", OP_CODE::FORMAT},
        {L"trigon", OP_CODE::TRIGON},
        {L"degtorad", OP_CODE::DEGTORAD},
        {L"radtodeg", OP_CODE::RADTODEG},
        {L"variance", OP_CODE::VARIANCE},
        {L"castchk", OP_CODE::CASTCHK},
        {L"finalize", OP_CODE::FINALIZE},
        {L"const", OP_CODE::CONST},
        {L"isconst", OP_CODE::ISCONST},
        {L"inst", OP_CODE::INSTRUCT},
        {L"e", OP_CODE::E},
        {L"parse", OP_CODE::PARSE},
        {L"unparse", OP_CODE::UNPARSE},
        {L"pe", OP_CODE::PE},
        {L"if", OP_CODE::IF},
        {L"for", OP_CODE::FOR},
        {L"break", OP_CODE::BREAK},
        {L"continue", OP_CODE::CONTINUE},
        {L"while", OP_CODE::WHILE},
        {L"dowhile", OP_CODE::DOWHILE},
        {L"switch", OP_CODE::SWITCH},
        {L"iscode", OP_CODE::ISCODE},
        {L"sconst", OP_CODE::SCONST},
        {L"sfinalize", OP_CODE::SFINALIZE},
        {L"plzdontcrash", OP_CODE::PLZDONTCRASH},
        {L"plzshutup", OP_CODE::PLZSHUTUP},
        {L"try", OP_CODE::TRY},
        {L"throw", OP_CODE::THROW},
        {L"parallel", OP_CODE::PARALLEL},
        {L"getchar", OP_CODE::GETCHAR},
        {L"setchar", OP_CODE::SETCHAR},
        {L">", OP_CODE::ARROW},
        {L">>", OP_CODE::CHEVRON},
        {L"plztrustme", OP_CODE::PLZTRUSTME},
        {L"icount", OP_CODE::ICOUNT}
    };
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Правила валидации для инструкций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct VRules {
    std::unordered_map<OP_CODE, std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::vector<int>>>>> ValidateRulesMap = {
        {OP_CODE::NOP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {0}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {-1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {-1, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::END, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::SLEEP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::VAR, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 1, 2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::PRINT, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"minimal", {1}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::FREE, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"minimal", {1}}}},
                        {L"requiredVar", {{L"param_nums", {-1, 0}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {-1, 0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::LABEL, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}},
                        {L"requiredLabel", {{L"param_nums", {0}}}},
                        {L"checkExistLabel", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::JUMP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::INPT, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::CHANGE, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::TO, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 2, 3}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::CALC, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"range", {2, 4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::NEWTEMP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::FORGET, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 0, 1}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::TCOUNT, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::ISSET, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::TYPEOF, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::COMP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::LOGIC, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 3, 4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::JIF, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::JIFNOT, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::DLABEL, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}},
                        {L"requiredLabel", {{L"param_nums", {0}}}},
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, -1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::SWAP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}},
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::ARRAY, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"minimal", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::VTOARR, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"minimal", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::PUSHB, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::POPB, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 1, 2}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::PUSHF, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::POPF,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 1, 2}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::ERASE,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 2, 3}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}, {L"condition", {2, 3}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}, {L"condition", {2, 3}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::INSRT, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {3}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::CLEAR, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {1}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::SIZEARR, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::SLICE, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::MERGE,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 2, 3}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::SORT,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 2, 3}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::UNIQUE,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 2, 3}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate",
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::REVERSE, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"variants", {2, 1, 2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::EQUAL, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::INNER, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::INALL, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::RINNER, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::RINALL, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::ARRTOMAP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::INTERS, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::NOTINTERS, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::ARRTOSTR, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {3}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::SUM, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::AVG, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::MIN, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::MAX, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::RNGE, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::MEDIAN, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::MODE, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::STDDEV, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::PUSH, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {3}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::VTOMAP, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"minimal", {3}}}},
                        {L"module", {{L"param_nums", {1, 2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::GETVALS, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::GETKEYS, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::GETINTERF, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::KVINTERS, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::KVNOTINTERS, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {4}}}},
                        {L"requiredVar", {{L"param_nums", {1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {1}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {1, 2}}}}}},
                {L"modeparams", {{L"param", {{L"count", {1}}}}}}
            }
        },
        {OP_CODE::CLEARC, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {0}}}}
                    }
                },
                {L"validate", {}},
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::TOINTERF, 
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {3}}}},
                        {L"requiredVar", {{L"param_nums", {0}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::UNINTERF,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {3}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        {OP_CODE::INTERFTOMAP,
            {
                {L"prevalidate", 
                    {
                        {L"checkParameterCount", {{L"stricted", {2}}}},
                        {L"requiredVar", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"validate", 
                    {
                        {L"checkNotExistValue", {{L"param_nums", {0, 1}}}}
                    }
                },
                {L"arrow", {{L"param_replace", {{L"number", {0}}}}}},
                {L"chevron", {{L"param_replace", {{L"number", {0, 1}}}}}},
                {L"modeparams", {{L"param", {{L"count", {0}}}}}}
            }
        },
        /*
        {L"rand", OP_CODE::RAND},
        {L"t", OP_CODE::T},
        {L"hrt", OP_CODE::HRT},
        {L"between", OP_CODE::BETWEEN},
        {L"jifelse", OP_CODE::JIFELSE},
        {L"jswitch", OP_CODE::JSWITCH},
        {L"format", OP_CODE::FORMAT},
        {L"trigon", OP_CODE::TRIGON},
        {L"degtorad", OP_CODE::DEGTORAD},
        {L"radtodeg", OP_CODE::RADTODEG},
        {L"variance", OP_CODE::VARIANCE},
        {L"castchk", OP_CODE::CASTCHK},
        {L"finalize", OP_CODE::FINALIZE},
        {L"const", OP_CODE::CONST},
        {L"isconst", OP_CODE::ISCONST},
        {L"inst", OP_CODE::INSTRUCT},
        {L"e", OP_CODE::E},
        {L"parse", OP_CODE::PARSE},
        {L"unparse", OP_CODE::UNPARSE},
        {L"pe", OP_CODE::PE},
        {L"if", OP_CODE::IF},
        {L"for", OP_CODE::FOR},
        {L"break", OP_CODE::BREAK},
        {L"continue", OP_CODE::CONTINUE},
        {L"while", OP_CODE::WHILE},
        {L"dowhile", OP_CODE::DOWHILE},
        {L"switch", OP_CODE::SWITCH},
        {L"iscode", OP_CODE::ISCODE},
        {L"sconst", OP_CODE::SCONST},
        {L"sfinalize", OP_CODE::SFINALIZE},
        {L"plzdontcrash", OP_CODE::PLZDONTCRASH},
        {L"plzshutup", OP_CODE::PLZSHUTUP},
        {L"try", OP_CODE::TRY},
        {L"throw", OP_CODE::THROW},
        {L"parallel", OP_CODE::PARALLEL},
        {L"getchar", OP_CODE::GETCHAR},
        {L"setchar", OP_CODE::SETCHAR},
        {L">", OP_CODE::ARROW},
        {L">>", OP_CODE::CHEVRON},
        {L"plztrustme", OP_CODE::PLZTRUSTME},
        {L"icount", OP_CODE::ICOUNT}
        */
    };
};