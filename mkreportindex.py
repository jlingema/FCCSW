import argparse
import collections
import os
import base64
import sys
sys.path.append('/afs/cern.ch/user/d/daho/SAS-build/scripts')
import common
import checkformat

def get_diff_map(file_name):
    '''
    generates the diffmap for a single file
    '''
    clang_format_output, num_violations = common.CheckFormattingRules(file_name)
    if num_violations != 0:
        return common._ComparisonReport(file_name, clang_format_output)
    else:
        return False

def report_name(path, file_name):
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
        source_files = filter(common._IsSourceFile, files)
        error_dict[path] = []
        for file_name in source_files:
            diff_map = get_diff_map(path + "/" + file_name)
            if diff_map:
                total_errors += 1
                error_dict[path].append(file_name)
                diff_map_name = report_name(path, file_name)
                with open(os.path.join(report_dir, diff_map_name), "w") as fobj:
                    fobj.write(diff_map)
    return (error_dict, total_errors)

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Formatter summary creator", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('source_dir', type=str, help='path to the source directory')
    parser.add_argument('report_dir', type=str, help='path to the report directory')
    args = parser.parse_args()

    llvm = "/afs/cern.ch/sw/lcg/external/llvm/3.6/x86_64-slc6/"
    os.environ["LD_LIBRARY_PATH"] = llvm+"lib64:"+os.environ["LD_LIBRARY_PATH"]
    os.environ["PATH"] = llvm+"bin:"+os.environ["PATH"]
    if not os.path.isfile(".clang-format"):
        shutil.copy("/afs/cern.ch/exp/fcc/sw/0.6/SAS/0.1.4/x86_64-slc6-clang3.6-opt/config/FCCSW-clang-format.yaml", ".clang-format")

    base_dir = os.path.abspath(args.source_dir.rstrip(os.sep))
    base_depth = len(base_dir.split(os.sep))
    depth = base_depth

    error_dict, total_errors = write_report_files(base_dir, args.report_dir)

    substrings = []
    visited = []

    for path in error_dict.keys():
        current_string = ""
        # close the divs as needed
        if path != base_dir:
            prev_depth = len(visited[-1].split(os.sep))
            depth = len(path.split(os.sep))
            visited.append(path)
            if depth <= prev_depth:
                while depth <= prev_depth:
                    substrings.append("</div>")
                    prev_depth -= 1
        else:
            visited.append(path)
        # create link + div for next sub-group
        current_string = "<a href='#{id}' class='list-group-item' data-toggle='collapse'><i class='glyphicon glyphicon-chevron-right'></i> {name} <span class='badge'>{n}</span></a>\n<div id='{id}' class='list-group collapse'>"
        # count the total number of errors found in sub-directories
        cntr = 0
        for path_name in error_dict.keys():
            if path in path_name:
                cntr += len(error_dict[path_name])
        current_string = current_string.format(id=path.replace(os.sep, "_").replace(".", "")[1:], name=os.path.basename(path), n=cntr)
        substrings.append(current_string)
        # append any files that contain formatting violations
        if len(error_dict[path]) != 0:
            for file_name in error_dict[path]:
                diff_map_name = report_name(path, file_name)
                substrings.append("<a class='list-group-item file-item' data-url='{diff_map_name}'>{title}</a>".format(diff_map_name=diff_map_name, title=file_name))

    while depth >= base_depth:
        substrings.append("</div>")
        depth -= 1

    # populate template from ./html/
    with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "html/report_index.html.in"), "r") as fobj:
        report_template = fobj.read()
    with open(os.path.join(args.report_dir, "index.html"), "w") as fobj:
        fobj.write(report_template.format(links="\n".join(substrings), title=os.path.basename(base_dir), n=total_errors))
    print("--------------------------------------------------------------------------------")
    print("Check Complete\nNumber of errors found: {total_errors}\nReport index at: {index_path}".format(total_errors=total_errors, index_path=os.path.abspath(os.path.join(args.report_dir, "index.html"))))
    print("--------------------------------------------------------------------------------")