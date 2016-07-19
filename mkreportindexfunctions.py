import argparse
import collections
import os
import base64
import datetime
import sys
sys.path.append('/afs/cern.ch/user/d/daho/SAS-build/scripts')
import common

def parse_args():
    '''
    Parses the arguments passed to the checker
    '''
    parser = argparse.ArgumentParser("Formatter summary creator", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('source_dir', type=str, help='path to the source directory')
    parser.add_argument('report_dir', type=str, help='path to the report directory')
    return parser.parse_args()

def set_environment():
    '''
    Sets the required environment variables
    '''
    llvm = "/afs/cern.ch/sw/lcg/external/llvm/3.6/x86_64-slc6/"
    os.environ["LD_LIBRARY_PATH"] = llvm+"lib64:"+os.environ["LD_LIBRARY_PATH"]
    os.environ["PATH"] = llvm+"bin:"+os.environ["PATH"]
    if not os.path.isfile(".clang-format"):
        shutil.copy("/afs/cern.ch/exp/fcc/sw/0.6/SAS/0.1.4/x86_64-slc6-clang3.6-opt/config/FCCSW-clang-format.yaml", ".clang-format")


def get_diff_map(file_name):
    '''
    generates the diffmap for a single file
    '''
    clang_format_output, num_violations = common.CheckFormattingRules(file_name)
    if num_violations != 0:
        return common._ComparisonReport(file_name, clang_format_output)
    else:
        return False

def generate_report_name(path, file_name):
    '''
    Generates a name for the report file based on the path and file name
    '''
    path_hash = base64.b64encode(path)
    return "report_{path_hash}_{file_name}.html".format(path_hash=path_hash, file_name=file_name)


def write_report_files(source_dir, report_dir):
    '''
    writes an html report file for each file in the source directory with coding standard violations
    '''
    error_dict = collections.OrderedDict()
    total_errors = 0
    for path, directories, files in os.walk(source_dir):
        print("checking %s" % path)
        source_files = filter(common._IsSourceFile, files)
        error_dict[path] = []
        for file_name in source_files:
            diff_map = get_diff_map(os.path.join(path, file_name))
            if diff_map:
                total_errors += 1
                error_dict[path].append(file_name)
                diff_map_name = generate_report_name(path, file_name)
                with open(os.path.join(report_dir, diff_map_name), "w") as fobj:
                    fobj.write(diff_map)
    return (error_dict, total_errors)